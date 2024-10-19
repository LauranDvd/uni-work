from unittest import TestCase

from src.domain.duplicate_name_exception import DuplicateName
from src.repository.client_repo import ClientRepo
from src.repository.movie_repo import MovieRepo
from src.repository.rental_repo import RentalRepo
from src.services.client_service import ClientService
from src.services.rental_service import RentalService


class TestClientService(TestCase):
    def setUp(self) -> None:
        self.client_repo = ClientRepo()
        self.movie_repo = MovieRepo()
        self.rental_repo = RentalRepo()
        self.rental_service = RentalService(self.rental_repo, self.client_repo, self.movie_repo)
        self.client_service = ClientService(self.client_repo, self.rental_service)

    def tearDown(self) -> None:
        del self.client_repo
        del self.movie_repo
        del self.rental_repo

    def test_add_client(self):
        self.client_service.add_client("John")
        all_clients = self.client_service.get_all_clients()
        found = False
        for client in all_clients:
            if client.name == "John":
                found = True

        self.assertTrue(found)

    def test_add_client_2(self):
        self.client_service.add_client("Mary")
        self.client_service.add_client("Ana")
        all_clients = self.client_service.get_all_clients()

        self.assertEqual(len(all_clients), 2)

    def test_add_client_duplicate_name(self):
        self.client_service.add_client("Ionut")
        with self.assertRaises(DuplicateName):
            self.client_service.add_client("Ionut")

    def test_add_client_nothing_unwanted(self):
        # Check len() is right
        self.client_service.add_client("Rares")
        self.client_service.add_client("Romulus")
        self.client_service.add_client("Arthur")
        self.client_service.add_client("Didi")

        all_clients = self.client_service.get_all_clients()
        self.assertEqual(len(all_clients), 4)
