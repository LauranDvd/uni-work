import random
from datetime import datetime
from dataclasses import dataclass


class Movie:
    def __init__(self, movie_id, name, description, genre):
        self._movie_id = movie_id
        self._name = name
        self.description = description
        self.genre = genre

    @staticmethod
    def random_name():
        name = random.choice(["Breathless", "Forrest Gump", "400 Blows", "Celine and Julie Go Boating", "Weekend",
                              "Day at Night", "Contempt", "Pierrot le Fou", "La Belle Noiseuse", "Rosemarys Baby",
                              "The Blue Ray", "High and Low", "Balanta", "Moartea dlui Lazarescu", "Jurassic Park",
                              "Gotti", "Mon Apocatastase Personnelle", "Schindlers List", "4 months 3 weeks 2 days"])
        return name

    @staticmethod
    def random_genre():
        genre = random.choice(["crime", "drama", "arthouse", "comedy", "thriller"])
        return genre

    @property
    def id(self):
        return self._movie_id

    @id.setter
    def id(self, value):
        self._movie_id = value

    @property
    def name(self):
        return self._name

    def __str__(self):
        return str(self.id) + ". " + self._name + " // " + self.description + " (" + self.genre + ")"


@dataclass
class Client:
    id: int
    name: str

    def __str__(self):
        return str(self.id) + ". " + self.name

    @staticmethod
    def random_name():
        """
        Get a random name
        :return: the name (str)
        """
        name = random.choice(["John", "Mary", "Ioana", "Ionut", "Andrei", "Paul", "David", "Eliza",
                              "James", "Robert", "Thomas", "Bianca", "Ringo", "Radu", "Silvia",
                              "Cristi", "Christian", "Jesus", "Charles", "Charlie", "Christ", "Dave", "Maria",
                              "Marshall", "Pierce", "Cristiano", "Joe", "Jean", "Luc",
                              "Francois", "Agatha", "Agnes", "Jacques", "Emmanuelle", "Manuela", "Marcela",
                              "Ion", "Ioan", "George", "Saul"])
        return name


@dataclass
class Rental:
    id: int
    movie_id: int
    client_id: int

    rented_date: datetime.date
    due_date: datetime.date
    returned_date: datetime.date

    def days_taken(self):
        """
        For how many days it was rented.
        :return: int
        """
        if self.returned_date < datetime.strptime("2000-01-01", "%Y-%M-%d"):  # not returned
            return (datetime.today() - self.rented_date).days
        else:
            return (self.returned_date - self.rented_date).days

    def is_late(self):
        return self.returned_date < datetime.strptime("2000-01-01", "%Y-%M-%d") and self.due_date < datetime.today()

    def days_late(self):
        return (datetime.today() - self.due_date).days

    def __str__(self):
        rented_str = self.rented_date.strftime("%Y-%m-%d")
        returned_str = self.returned_date.strftime("%Y-%m-%d")
        return "Client #" + str(self.client_id) + " rented movie #" + str(self.movie_id) + " in " + rented_str +\
            "and returned it in" + returned_str
