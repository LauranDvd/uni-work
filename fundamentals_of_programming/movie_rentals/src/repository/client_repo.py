from src.domain.duplicate_name_exception import DuplicateName
from src.repository.generic_repo import GenericRepo


class ClientRepo(GenericRepo):
    def __init__(self):
        super().__init__()

    def save(self, item):
        """
        In addition to super():
        :raises: DuplicateName if the name is already in use
        """
        if self.find_by_name(item.name) is not None:
            raise DuplicateName()
        super().save(item)
