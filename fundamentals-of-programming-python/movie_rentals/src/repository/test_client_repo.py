from unittest import TestCase

from src.domain.duplicate_id_exception import DuplicateID
from src.domain.duplicate_name_exception import DuplicateName
from src.domain.entities import Client
from src.repository.client_repo import ClientRepo


class TestClientRepo(TestCase):
    def setUp(self) -> None:
        self.client_repo = ClientRepo()

    def tearDown(self) -> None:
        del self.client_repo

    def test_save_basic(self):
        client = Client(7, "Andreea")
        self.client_repo.save(client)
        self.assertEqual(self.client_repo.all_items[client.id], client)

    def test_save_basic_2(self):
        client = Client(233, "Andreea")
        client_2 = Client(722, "Andrei")
        self.client_repo.save(client)
        self.client_repo.save(client_2)
        self.assertEqual(self.client_repo.find_all(), [client, client_2])

    def test_save_duplicate_id(self):
        client = Client(72, "Dorel")
        self.client_repo.save(client)

        client_2 = Client(72, "Eliza")
        with self.assertRaises(DuplicateID):
            self.client_repo.save(client_2)

    def test_save_duplicate_name(self):
        client = Client(72, "Dorel")
        self.client_repo.save(client)

        client_2 = Client(12, "Dorel")
        with self.assertRaises(DuplicateName):
            self.client_repo.save(client_2)
