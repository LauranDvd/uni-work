import random

from src.domain.duplicate_id_exception import DuplicateID
from src.domain.duplicate_name_exception import DuplicateName
from src.domain.entities import Movie
from src.domain.item_not_found_exception import MovieNotFound


class MovieService:
    def __init__(self, movie_repo, rental_service):
        self.__movie_repo = movie_repo
        self.__rental_service = rental_service

    def generate_random(self):
        for x in range(20):
            try:
                self.add_movie(random.randint(1, 1000), Movie.random_name(), "Movie about some stuff", Movie.random_genre())
            except DuplicateID:
                pass
            except DuplicateName:
                pass

    def add_movie(self, id, name, description, genre):
        movie = Movie(id, name, description, genre)
        self.__movie_repo.save(movie)

    def get_all_movies(self):
        return self.__movie_repo.find_all()

    def remove_movie(self, name):
        movie = self.__movie_repo.find_by_name(name)
        if movie is not None:
            self.__movie_repo.delete_by_id(movie.id)
        else:
            raise MovieNotFound

        # 2. delete movie's rentals
        rentals = self.__rental_service.filter_by_movie(movie)
        for rent in rentals:
            self.__rental_service.delete_by_id(rent.id)

    def update_movie(self, old_name, name, description, genre):
        movie = self.__movie_repo.find_by_name(old_name)
        if movie is None:
            raise MovieNotFound()
        new_movie = Movie(movie.id, name, description, genre)

        self.__movie_repo.update_item(movie.id, new_movie)

    @staticmethod
    def jaccard_similarity(a, b):
        """
        Similarity of two strings
        :param a: str
        :param b: str
        :return: float
        """
        return len(set(a) & set(b)) / len(set(a) | set(b))

    @staticmethod
    def partial_match(a, b):
        return MovieService.jaccard_similarity(a, b) > 0.8

    @staticmethod
    def __fits_query(movie, query):
        # 1. [query] == id
        if query.isnumeric():
            if int(query) == movie.id:
                return True

        # 2. [query] is similar to movie.name or description or genre
        if query.lower() in movie.name.lower() or MovieService.partial_match(query.lower(), movie.name.lower())\
                or query.lower() in movie.description.lower() or MovieService.partial_match(query.lower(), movie.description.lower())\
                or query.lower() in movie.genre.lower() or MovieService.partial_match(query.lower(), movie.genre.lower()):
            return True

        return False

    def search_movies(self, query):
        """
        Return movies whose id/name contains [query]
        :param query: str
        :return: list of Movie objects
        """
        ret = []
        for movie in self.get_all_movies():
            if MovieService.__fits_query(movie, query):
                ret.append(movie)
        return ret
