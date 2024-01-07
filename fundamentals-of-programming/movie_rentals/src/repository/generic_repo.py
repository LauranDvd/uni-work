from src.domain.duplicate_name_exception import DuplicateName
from src.domain.item_not_found_exception import ItemNotFound
from src.domain.duplicate_id_exception import DuplicateID


class GenericRepo:
    def __init__(self):
        self.all_items = {}

    def save(self, item):
        """
        Save an instance of the class

        :param item: object of class Client/Movie/Rental
        :raises: DuplicateID if there's already a user/movie/rental with same ID
        """
        if item.id in self.all_items:
            raise DuplicateID()
        self.all_items[item.id] = item

    def find_by_id(self, id):
        for key in self.all_items:
            if self.all_items[key].id == id:
                return self.all_items[key]
        return None  # or raise ItemNotFound?

    def find_by_name(self, name):
        for key in self.all_items:
            if self.all_items[key].name == name:
                return self.all_items[key]
        return None  # or raise?

    def delete_by_id(self, id):
        if id in self.all_items:
            self.all_items.pop(id)

    def update_item(self, id, item):
        if id not in self.all_items:
            raise ItemNotFound()
        else:
            self.all_items[id] = item

    def find_all(self):
        """
        All clients.
        :return: list of Client objects.
        """
        ret = []
        for id in self.all_items:
            ret.append(self.all_items[id])
        return ret
