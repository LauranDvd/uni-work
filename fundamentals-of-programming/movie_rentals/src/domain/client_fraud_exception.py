class ClientFraud(Exception):
    def __init__(self, message="That client has unreturned movies past their due date"):
        self._message = message

    def __str__(self):
        return self._message
