from unittest import TestCase

from domain.move_error import MoveError


class TestMoveError(TestCase):
    def test_str(self):
        err = MoveError("You cannot")
        self.assertEqual(str(err), "You cannot")
        self.assertEqual(err._msg, "You cannot")
