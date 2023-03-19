from datetime import datetime

from src.repository.generic_repo import GenericRepo


class RentalRepo(GenericRepo):
    def __init__(self):
        super().__init__()

    def find_by_client_movie_id(self, client_id, movie_id):
        # movies not returned have a higher priority
        for rental in self.all_items.values():
            if rental.client_id == client_id and rental.movie_id == movie_id and rental.returned_date <\
                    datetime.strptime("2020-01-01", "%Y-%M-%d"):
                return rental
        for rental in self.all_items.values():
            if rental.client_id == client_id and rental.movie_id == movie_id:
                return rental

        return None
