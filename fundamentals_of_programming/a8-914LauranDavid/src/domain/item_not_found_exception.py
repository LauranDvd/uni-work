from src.domain.repo_exception import RepoException


class ItemNotFound(RepoException):
    def __init__(self, msg="There's no such thing"):
        super().__init__(msg)


class MovieNotFound(ItemNotFound):
    def __init__(self, msg="There's no such movie"):
        super().__init__(msg)


class ClientNotFound(ItemNotFound):
    def __init__(self, msg="There's no such client"):
        super().__init__(msg)


class RentalNotFound(ItemNotFound):
    def __init__(self, msg="There's no such rental"):
        super().__init__(msg)
