class RepoException(Exception):
    def __init__(self, msg="Something went wrong"):
        self._message = msg

    def __str__(self):
        return self._message
