from unittest import TestCase

from domain.entities import Board, Cell


class TestBoard(TestCase):
    def setUp(self) -> None:
        self._board = Board(7, 7)

    def tearDown(self) -> None:
        del self._board

    def test_basic(self):
        self.assertEqual(self._board.lines, 7)
        self.assertEqual(self._board.cols, 7)

    def test_set_cell(self):
        self._board.set_cell(2, 5, "user")
        self.assertEqual(self._board.get_cell(2, 5).value, "user")
        self._board.set_cell(6, 0, "computer")
        self.assertEqual(self._board.get_cell(6, 0).value, "computer")

    def test_is_inside(self):
        self.assertEqual(self._board.is_inside(1, 6), True)
        self.assertEqual(self._board.is_inside(6, 6), True)
        self.assertEqual(self._board.is_inside(0, 4), True)
        self.assertEqual(self._board.is_inside(7, 7), False)
        self.assertEqual(self._board.is_inside(-2, 3), False)
        self.assertEqual(self._board.is_inside(8, 2), False)

    def test_is_full(self):
        self.assertEqual(self._board.is_full(), False)

        # fill first line
        for j in range(self._board.cols):
            self._board.set_cell(0, j, "computer")
        self.assertEqual(self._board.is_full(), False)

        for i in range(1, self._board.lines):
            for j in range(self._board.cols):
                self._board.set_cell(i, j, "user")
        self.assertEqual(self._board.is_full(), True)

    def test_is_cell_free(self):
        self.assertEqual(self._board.is_cell_free(2, 3), True)
        self.assertEqual(self._board.is_cell_free(self._board.lines - 1, self._board.cols - 1), True)

        self._board.set_cell(1, 2, "user")
        self.assertEqual(self._board.is_cell_free(1, 2), False)


class TestCell(TestCase):
    def setUp(self) -> None:
        self._cell = Cell()

    def tearDown(self) -> None:
        del self._cell

    def test_value(self):
        self.assertEqual(self._cell.value, "nothing")
        self._cell.value = "user"
        self.assertEqual(self._cell.value, "user")

    def test_is_empty(self):
        self.assertEqual(self._cell.is_empty(), True)
        self._cell.value = "computer"
        self.assertEqual(self._cell.is_empty(), False)
