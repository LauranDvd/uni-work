import random
from datetime import datetime, timedelta

from src.domain.client_fraud_exception import ClientFraud
from src.domain.duplicate_id_exception import DuplicateID
from src.domain.item_not_found_exception import ItemNotFound, MovieNotFound, ClientNotFound, RentalNotFound
from src.domain.dto import DtoMovieDays, DtoClientDays, DtoMovieClientDays
from src.domain.entities import Rental


class RentalService:
    def __init__(self, rental_repo, client_repo, movie_repo):
        self.__rental_repo = rental_repo
        self.__movie_repo = movie_repo
        self.__client_repo = client_repo

    def generate_random(self):
        all_client_ids = [x.id for x in self.__client_repo.find_all()]
        all_movie_ids = [x.id for x in self.__movie_repo.find_all()]

        for i in range(20):
            client_id = random.choice(all_client_ids)
            movie_id = random.choice(all_movie_ids)
            days = random.randint(0, 10)

            try:
                self.rent_movie(client_id, movie_id, days)
            except ClientFraud:
                pass  # let it be
            except DuplicateID:
                pass

    def get_all_rentals(self):
        return self.__rental_repo.find_all()

    def get_all_rentals_nice(self):
        lst = self.get_all_rentals()
        nice = []
        for rent in lst:
            client = self.__client_repo.find_by_id(rent.client_id)
            movie = self.__movie_repo.find_by_id(rent.movie_id)
            rented_str = rent.rented_date.strftime("%Y-%m-%d")
            returned_str = rent.returned_date.strftime("%Y-%m-%d")

            here = client.name + " rented \"" + movie.name + "\" in " + rented_str
            if rent.returned_date < datetime.strptime("2000-01-01", "%Y-%M-%d"):
                here += " and didn't return it."
            else:
                here += " and returned it in " + returned_str
            nice.append(here)

        return nice

    def delete_by_id(self, id):
        self.__rental_repo.delete_by_id(id)

    def filter_by_client(self, client):
        rentals = self.get_all_rentals()
        ret = []
        for rent in rentals:
            if rent.client_id == client.id:
                ret.append(rent)
        return ret

    def filter_by_movie(self, movie):
        rentals = self.get_all_rentals()
        ret = []
        for rent in rentals:
            if rent.movie_id == movie.id:
                ret.append(rent)
        return ret

    def can_rent(self, client_id):
        # i.e., they don't have rented movies past their due date
        all_rentals = self.get_all_rentals()
        for rental in all_rentals:
            if rental.client_id == client_id:
                if rental.returned_date < datetime.strptime("2000-01-01", "%Y-%M-%d") and \
                        rental.due_date < datetime.today():
                    return False
        return True

    def rent_movie(self, client_id, movie_id, days):
        if self.__client_repo.find_by_id(client_id) is None:
            raise ClientNotFound()
        if self.__movie_repo.find_by_id(movie_id) is None:
            raise MovieNotFound()

        if self.can_rent(client_id):
            rented_date = datetime.today() - timedelta(days=7)  # for testing purposes
            due_date = rented_date + timedelta(days=days)
            returned_date = datetime.strptime("1975-01-01", "%Y-%M-%d")
            rental = Rental(random.randint(1, 1000), movie_id, client_id, rented_date, due_date, returned_date)

            self.__rental_repo.save(rental)  # might raise DuplicateID
        else:
            raise ClientFraud()

    def return_movie(self, client_id, movie_id):
        if self.__rental_repo.find_by_client_movie_id(client_id, movie_id) is None:
            raise RentalNotFound

        rental = self.__rental_repo.find_by_client_movie_id(client_id, movie_id)
        rental.returned_date = datetime.today()

        self.__rental_repo.update_item(rental.id, rental)

    def update_rental(self, id, rented_date, due_date, returned_date):
        rental = self.__rental_repo.find_by_id(id)

        new_rental = rental.copy()
        new_rental.rented_date = rented_date
        new_rental.due_date = due_date
        new_rental.returned_date = returned_date

        self.__rental_repo.update_item(id, new_rental)

    def most_rented(self):
        days_rented = {}  # movie_id --> sum(days)
        for rental in self.get_all_rentals():
            movie = self.__movie_repo.find_by_id(rental.movie_id)
            if movie.id not in days_rented:
                days_rented.update({movie.id: 0})
            days_rented[movie.id] += rental.days_taken()

        dtos = []
        for movie_id in days_rented:
            dto_movie_days = DtoMovieDays(self.__movie_repo.find_by_id(movie_id), days_rented[movie_id])
            dtos.append(dto_movie_days)
        dtos.sort()
        dtos.reverse()
        return dtos

    def most_active(self):
        days_rented = {}  # client_id --> sum(days)
        for rental in self.get_all_rentals():
            try:
                client = self.__client_repo.find_by_id(rental.client_id)
            except ItemNotFound:  # this user was probably deleted
                continue
            if client.id not in days_rented:
                days_rented.update({client.id: 0})
            days_rented[client.id] += rental.days_taken()

        dtos = []
        for client_id in days_rented:
            dto_client_days = DtoClientDays(self.__client_repo.find_by_id(client_id), days_rented[client_id])
            dtos.append(dto_client_days)
        dtos.sort()
        dtos.reverse()
        return dtos

    def late_rentals(self):
        # for each late rental: dto(movie_title, client_name, days late)
        dtos = []
        for rental in self.get_all_rentals():
            if rental.is_late():
                try:
                    movie = self.__movie_repo.find_by_id(rental.movie_id)
                    client = self.__client_repo.find_by_id(rental.client_id)
                except ItemNotFound:  # movie or client were deleted
                    continue
                days = rental.days_late()
                dto_movie_client_days = DtoMovieClientDays(movie, client, days)
                dtos.append(dto_movie_client_days)

        dtos.sort()
        dtos.reverse()
        return dtos
