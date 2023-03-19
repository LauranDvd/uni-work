import random
from copy import copy

from src.domain.duplicate_name_exception import DuplicateName
from src.domain.item_not_found_exception import ClientNotFound
from src.domain.duplicate_id_exception import DuplicateID
from src.domain.entities import Client


class ClientService:
    def __init__(self, client_repo, rental_service):
        self.__client_repo = client_repo
        self.__rental_service = rental_service

    def generate_random(self):
        for x in range(80):
            try:
                self.add_client(Client.random_name())
            except DuplicateID:
                pass
            except DuplicateName:
                pass

    def add_client(self, name):
        """
        Add client to the repository
        (test git--ignore this line)
        :param name: str
        :raises: DuplicateID if we can't find a new ID
                 DuplicateName if [name] is already in use
        """
        id = random.randint(1, 1000)  # todo: make sure it's unique
        client = Client(id, name)
        self.__client_repo.save(client)

    def remove_client(self, name):
        client = self.__client_repo.find_by_name(name)
        if client is None:
            raise ClientNotFound()
        self.__client_repo.delete_by_id(client.id)

        # delete client's rentals
        rentals = self.__rental_service.filter_by_client(client)
        for rent in rentals:
            self.__rental_service.delete_by_id(rent.id)

    def update_client(self, old_name, new_name):
        client = self.__client_repo.find_by_name(old_name)
        if client is None:
            raise ClientNotFound()
        new_client = copy(client)
        new_client.name = new_name

        self.__client_repo.update_item(client.id, new_client)

    def get_all_clients(self):
        return self.__client_repo.find_all()

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
        return ClientService.jaccard_similarity(a, b) > 0.8

    @staticmethod
    def __fits_query(client, query):
        # 1. [query] == id
        if query.isnumeric():
            if int(query) == client.id:
                return True

        # 2. [query] is a substring of client.name
        if query.lower() in client.name.lower() or ClientService.partial_match(query.lower(), client.name.lower()):
            return True

        return False

    def search_clients(self, query):
        """
        Return clients whose id/name contains [query]
        :param query: str
        :return: list of Client objects
        """
        ret = []
        for client in self.get_all_clients():
            if ClientService.__fits_query(client, query):
                ret.append(client)
        return ret
