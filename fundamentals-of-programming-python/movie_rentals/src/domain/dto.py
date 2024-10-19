class DtoMovieDays:
    def __init__(self, movie, no_days):
        self.__movie_name = movie.name
        self.__days = no_days

    def __eq__(self, other):
        return self.__days == other.days

    def __lt__(self, other):
        return self.__days < other.days

    def __str__(self):
        return "Movie \"" + self.movie_name + "\" was rented for " + str(self.days) + " days."

    @property
    def movie_name(self):
        return self.__movie_name

    @property
    def days(self):
        return self.__days


class DtoClientDays:
    def __init__(self, client, no_days):
        self.__client_name = client.name
        self.__days = no_days

    def __eq__(self, other):
        return self.__days == other.days

    def __lt__(self, other):
        return self.__days < other.days

    def __str__(self):
        return "Client \"" + self.__client_name + "\" has rented movies for a total of " + str(self.__days) + " days."

    @property
    def client_name(self):
        return self.__client_name

    @property
    def days(self):
        return self.__days


class DtoMovieClientDays:
    def __init__(self, movie, client, no_days):
        self.__movie_name = movie.name
        self.__client_name = client.name
        self.__days = no_days

    def __eq__(self, other):
        return self.__days == other.days

    def __lt__(self, other):
        return self.__days < other.days

    def __str__(self):
        return "Movie \"" + self.movie_name + "\" rented by " + self.client_name + " is " + str(self.days) + " days late."

    @property
    def movie_name(self):
        return self.__movie_name

    @property
    def client_name(self):
        return self.__client_name

    @property
    def days(self):
        return self.__days
