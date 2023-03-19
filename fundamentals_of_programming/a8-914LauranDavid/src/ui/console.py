import random

from src.domain.client_fraud_exception import ClientFraud
from src.domain.repo_exception import RepoException


class Console:
    def __init__(self, movie_service, client_service, rental_service):
        self.__movie_service = movie_service
        self.__client_service = client_service
        self.__rental_service = rental_service

    def add_client(self):
        name = input("Their name: ")
        try:
            self.__client_service.add_client(name)
        except RepoException as e:
            print(e)

    def remove_client(self):
        name = input("Their name: ")
        try:
            self.__client_service.remove_client(name)
        except RepoException as e:
            print(e)

    def update_client(self):
        old_name = input("Their current name: ")

        new_name = input("Their new name: ")
        try:
            self.__client_service.update_client(old_name, new_name)
        except RepoException as e:
            print(e)

    def list_clients(self):
        all_clients = self.__client_service.get_all_clients()
        for client in all_clients:
            print(client)

    def clients_menu(self):
        print("[1] Add client")
        print("[2] Remove client")
        print("[3] Update client")
        print("[4] List clients")

        opt = input(">")
        try:
            opt = int(opt)
        except ValueError:
            print("Option should be a natural number")
        else:
            if opt == 1:
                self.add_client()
            elif opt == 2:
                self.remove_client()
            elif opt == 3:
                self.update_client()
            elif opt == 4:
                self.list_clients()
            else:
                print("Option not valid")

    def add_movie(self):
        name = input("Title: ")
        description = input("Description: ")
        genre = input("Genre: ")

        try:
            self.__movie_service.add_movie(random.randint(1, 1000), name, description, genre)  # todo: proper id?
        except RepoException as e:
            print(e)

    def remove_movie(self):
        name = input("Its name: ")
        try:
            self.__movie_service.remove_movie(name)
        except RepoException as e:
            print(e)

    def update_movie(self):
        old_name = input("Its current title: ")

        title = input("New title: ")
        description = input("New description: ")
        genre = input("New genre: ")
        try:
            self.__movie_service.update_movie(old_name, title, description, genre)
        except RepoException as e:
            print(e)

    def list_movies(self):
        all_movies = self.__movie_service.get_all_movies()
        for movie in all_movies:
            print(movie)

    def movies_menu(self):
        print("[1] Add movie")
        print("[2] Remove movie")
        print("[3] Update movie")
        print("[4] List movies")

        opt = input(">")
        try:
            opt = int(opt)
        except ValueError:
            print("Option should be a natural number")
        else:
            if opt == 1:
                self.add_movie()
            elif opt == 2:
                self.remove_movie()
            elif opt == 3:
                self.update_movie()
            elif opt == 4:
                self.list_movies()

    def rent_movie(self):
        try:
            client_id = int(input("Client's id: "))
            movie_id = int(input("Movie's id: "))
            days = int(input("Number of days for which they rent it: "))
        except ValueError:
            print("These should be numbers")
        else:
            try:
                self.__rental_service.rent_movie(client_id, movie_id, days)
            except RepoException as e:
                print(e)
            except ClientFraud as e:
                print(e)

    def return_movie(self):
        try:
            client_id = int(input("Client's id: "))
            movie_id = int(input("Movie's id: "))
        except ValueError:
            print("These should be numbers")
        else:
            try:
                self.__rental_service.return_movie(client_id, movie_id)
            except RepoException as e:
                print(e)

    def list_rentals(self):
        all_rentals = self.__rental_service.get_all_rentals_nice()
        for rental in all_rentals:
            print(rental)

    def rentals_menu(self):
        print("[1] Rent movie")
        print("[2] Return movie")
        print("[3] See all rentals")

        opt = input(">")
        try:
            opt = int(opt)
        except ValueError:
            print("Option should be a natural number")
        else:
            if opt == 1:
                self.rent_movie()
            elif opt == 2:
                self.return_movie()
            elif opt == 3:
                self.list_rentals()

    def search_clients(self):
        query = input(">")
        all_results = self.__client_service.search_clients(query)
        print("MATCHING ITEMS:")
        for result in all_results:
            print(result)

    def search_movies(self):
        query = input(">")
        all_results = self.__movie_service.search_movies(query)
        print("MATCHING ITEMS:")
        for result in all_results:
            print(result)

    def stats_most_rented(self):
        most_rented = self.__rental_service.most_rented()
        for dto in most_rented:
            print(dto)

    def stats_most_active(self):
        most_active = self.__rental_service.most_active()
        for dto in most_active:
            print(dto)

    def stats_late_rentals(self):
        late_rentals = self.__rental_service.late_rentals()
        for dto in late_rentals:
            print(dto)

    def statistics_menu(self):
        print("[1] Most rented movies")
        print("[2] Most active clients")
        print("[3] Late rentals")
        opt = input(">")

        try:
            opt = int(opt)
        except ValueError:
            print("Option should be a number")
        else:
            if opt == 1:
                self.stats_most_rented()
            elif opt == 2:
                self.stats_most_active()
            elif opt == 3:
                self.stats_late_rentals()

    def main_menu(self):
        while True:
            print("[1] Modify clients")
            print("[2] Modify movies")
            print("[3] Rent/return movie")
            print("[4] Search clients")
            print("[5] Search movies")
            print("[6] Statistics")

            opt = input(">")
            try:
                opt = int(opt)
            except ValueError:
                print("Option should be a natural number")
            else:
                if opt == 1:
                    self.clients_menu()
                elif opt == 2:
                    self.movies_menu()
                elif opt == 3:
                    self.rentals_menu()
                elif opt == 4:
                    self.search_clients()
                elif opt == 5:
                    self.search_movies()
                elif opt == 6:
                    self.statistics_menu()
                else:
                    print("Option not valid")
