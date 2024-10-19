from src.domain.repo_exception import RepoException


class DuplicateID(RepoException):
    def __init__(self, message="ID already in use"):
        super().__init__(message)
