from unittest import TestCase

from src.domain.entities import Client


class TestClient(TestCase):
    def setUp(self) -> None:
        pass

    def tearDown(self) -> None:
        pass

    def test_basic(self):
        client = Client(3, "David")
        self.assertEqual(client.id, 3)
        self.assertEqual(client.name, "David")

    def test_str(self):
        client = Client(7, "Paul")
        self.assertEqual(str(client), "7. Paul")
