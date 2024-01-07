from src.domain.repo_exception import RepoException


class DuplicateName(RepoException):
    def __init__(self, msg="Name already in use"):
        super().__init__(msg)
