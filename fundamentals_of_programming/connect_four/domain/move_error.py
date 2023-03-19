class MoveError(Exception):
    """
    Use when the user tries to make an illegal move
    """
    def __init__(self, msg):
        self._msg = msg

    def __str__(self):
        return self._msg
