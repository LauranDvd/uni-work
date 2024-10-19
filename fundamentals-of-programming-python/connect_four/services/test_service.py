from unittest import TestCase

from domain.entities import Board
from domain.move_error import MoveError
from services.service import Service


class TestService(TestCase):
    def setUp(self) -> None:
        self._board = Board(5, 7)
        self._service = Service(self._board)

    def tearDown(self) -> None:
        del self._board
        del self._service

    def test_next_move_2(self):
        # It used to fail
        self._board.set_cell(3, 0, "computer")
        self._board.set_cell(3, 1, "computer")
        self._board.set_cell(3, 2, "computer")

        self._board.set_cell(4, 0, "user")
        self._board.set_cell(4, 1, "computer")
        self._board.set_cell(4, 2, "user")

        nxt = self._service._find_next_move()
        # print(self._service._find_double_attack_move())
        self.assertTrue(self._service._is_movable(nxt[0], nxt[1]))

    def test_init_board(self):
        self._board.set_cell(3, 3, "computer")
        self._service.init_board()
        for i in range(self._service.board_lines):
            for j in range(self._service.board_cols):
                self.assertEqual(self._service.get_cell_value(i, j), "nothing")

    def test_board_lines(self):
        self.assertEqual(self._service.board_lines, self._board.lines)

    def test_board_cols(self):
        self.assertEqual(self._service.board_cols, self._board.cols)

    def test_get_cell_value(self):
        self.assertEqual(self._service.get_cell_value(3, 4), "nothing")
        self._board.set_cell(3, 4, "computer")
        self.assertEqual(self._service.get_cell_value(3, 4), "computer")

    def test_get_cell_value_nice(self):
        self.assertEqual(self._service.get_cell_value_nice(4, 0), ".")
        self._board.set_cell(4, 0, "user")
        self.assertEqual(self._service.get_cell_value_nice(4, 0), "x")
        self._board.set_cell(0, 5, "computer")
        self.assertEqual(self._service.get_cell_value_nice(0, 5), "0")

    def test__is_lifted(self):
        # Case 1. last line
        self.assertEqual(self._service._is_lifted(self._board.lines - 1, 2), True)

        # Case 2. occupied cells below it
        self.assertEqual(self._service._is_lifted(2, 5), False)
        self._board.set_cell(4, 5, "user")
        self.assertEqual(self._service._is_lifted(2, 5), False)
        self._board.set_cell(3, 5, "computer")
        self.assertEqual(self._service._is_lifted(2, 5), True)

    def test__is_movable(self):
        self._board.set_cell(4, 1, "user")
        self.assertEqual(self._service._is_movable(2, 1), False)
        self._board.set_cell(3, 1, "user")
        self.assertEqual(self._service._is_movable(2, 1), True)

        self.assertEqual(self._service._is_movable(self._board.lines + 1, 2), False)

        self._board.set_cell(4, 3, "computer")
        self.assertEqual(self._service._is_movable(4, 3), False)

    def test_move_user(self):
        # valid move
        self._board.set_cell(4, 2, "computer")
        self._service.move_user(2)
        self.assertEqual(self._board.get_cell(3, 2).value, "user")

        # MoveError: column doesn't exist
        with self.assertRaises(MoveError):
            self._service.move_user(8)

        # MoveError: full column
        for i in range(self._board.lines):
            self._service.move_user(3)
        with self.assertRaises(MoveError):
            self._service.move_user(3)

    def test__winning_move(self):
        self._board.set_cell(2, 1, "computer")
        self._board.set_cell(2, 2, "computer")
        self._board.set_cell(2, 4, "computer")

        self.assertEqual(self._service._winning_move(2, 3, "computer"), True)
        self.assertEqual(self._service._winning_move(2, 3, "user"), False)
        self.assertEqual(self._service._winning_move(2, 0, "computer"), False)

    def test__random_move(self):
        for it in range(100):
            line, col = self._service._random_move()
            self.assertTrue(0 <= line < self._board.lines)
            self.assertTrue(0 <= col < self._board.cols)

    def test__would_double_attack(self):
        # ....
        # ....
        # x.x.    (here, on the last column)
        # .0.x
        # 00.x
        self._board.set_cell(4, 0, "computer")
        self._board.set_cell(4, 1, "computer")
        self._board.set_cell(4, 3, "user")
        self._board.set_cell(3, 1, "computer")
        self._board.set_cell(3, 3, "user")
        self._board.set_cell(2, 0, "user")
        self.assertEqual(self._service._would_double_attack(2, 3, "user"), False)
        self._board.set_cell(2, 2, "user")
        self.assertEqual(self._service._would_double_attack(2, 3, "user"), True)

    def test__has_neighbor(self):
        self._board.set_cell(4, 3, "computer")
        self.assertTrue(self._service._has_neighbor(3, 2, "computer"))
        self.assertFalse(self._service._has_neighbor(3, 2, "user"))

    def test__find_win_block_move(self):
        # ....
        # ....        win: (1, 1) and block: (1, 3)
        # x0xx
        # .0.x
        # 00.x
        self.assertEqual(self._service._find_win_block_move(), (-1, -1, -1, -1))

        self._board.set_cell(4, 0, "computer")
        self._board.set_cell(4, 1, "computer")
        self._board.set_cell(4, 3, "user")
        self._board.set_cell(3, 1, "computer")
        self._board.set_cell(3, 3, "user")
        self._board.set_cell(2, 0, "user")
        self._board.set_cell(2, 1, "computer")
        self._board.set_cell(2, 2, "user")
        self.assertEqual(self._service._find_win_block_move(), (1, 1, -1, -1))
        self._board.set_cell(2, 3, "user")

        self.assertEqual(self._service._find_win_block_move(), (1, 1, 1, 3))

    def test__find_double_attack_move(self):
        # Same example as in the related function, but with players inverted
        self._board.set_cell(4, 0, "user")
        self._board.set_cell(4, 1, "user")
        self._board.set_cell(4, 3, "computer")
        self._board.set_cell(3, 1, "user")
        self._board.set_cell(3, 3, "computer")
        self.assertEqual(self._service._find_double_attack_move(), (-1, -1))
        self._board.set_cell(2, 0, "computer")
        self._board.set_cell(2, 2, "computer")
        self.assertEqual(self._service._find_double_attack_move(), (2, 3))

    def test__find_neighboring_move(self):
        # ....
        # 0..x        => (4, 1), (-1, -1)
        self._board.set_cell(4, 0, "computer")
        self._board.set_cell(4, 3, "user")
        self.assertEqual(self._service._find_neighboring_move(), (4, 1, -1, -1))

    def test_is_streak_here(self):
        # .....
        # ....x
        # .0.x0
        # x0xx0
        # 0x0x0         starts from (4,1) in direction 1
        self._board.set_cell(4, 0, "computer")
        self._board.set_cell(4, 1, "user")
        self._board.set_cell(4, 2, "computer")
        self._board.set_cell(4, 3, "user")
        self._board.set_cell(4, 4, "computer")

        self._board.set_cell(3, 0, "user")
        self._board.set_cell(3, 1, "computer")
        self._board.set_cell(3, 2, "user")
        self._board.set_cell(3, 3, "user")
        self._board.set_cell(3, 4, "computer")

        self._board.set_cell(2, 1, "computer")
        self._board.set_cell(2, 3, "user")
        self._board.set_cell(2, 4, "computer")

        self.assertFalse(self._service.is_streak_here(4, 1, 1))
        self._board.set_cell(1, 4, "user")

        self.assertTrue(self._service.is_streak_here(4, 1, 1))
        self.assertFalse(self._service.is_streak_here(3, 2, 1))

    def test_is_winner(self):
        # Same example as in text_is_streak_here
        self._board.set_cell(4, 0, "computer")
        self._board.set_cell(4, 1, "user")
        self._board.set_cell(4, 2, "computer")
        self._board.set_cell(4, 3, "user")
        self._board.set_cell(4, 4, "computer")

        self._board.set_cell(3, 0, "user")
        self._board.set_cell(3, 1, "computer")
        self._board.set_cell(3, 2, "user")
        self._board.set_cell(3, 3, "user")
        self._board.set_cell(3, 4, "computer")

        self._board.set_cell(2, 1, "computer")
        self._board.set_cell(2, 3, "user")
        self._board.set_cell(2, 4, "computer")

        self.assertFalse(self._service.is_winner())
        self._board.set_cell(1, 4, "user")

        self.assertTrue(self._service.is_winner())

    def test_get_special_print_cells(self):
        # Same example as in test_is_streak_here
        self._board.set_cell(4, 0, "computer")
        self._board.set_cell(4, 1, "user")
        self._board.set_cell(4, 2, "computer")
        self._board.set_cell(4, 3, "user")
        self._board.set_cell(4, 4, "computer")

        self._board.set_cell(3, 0, "user")
        self._board.set_cell(3, 1, "computer")
        self._board.set_cell(3, 2, "user")
        self._board.set_cell(3, 3, "user")
        self._board.set_cell(3, 4, "computer")

        self._board.set_cell(2, 1, "computer")
        self._board.set_cell(2, 3, "user")
        self._board.set_cell(2, 4, "computer")

        self._board.set_cell(1, 4, "user")

        special = self._service.get_special_print_cells()
        self.assertTrue(special[1][4])
        self.assertTrue(special[3][2])
        self.assertTrue(special[4][1])

        self.assertFalse(special[4][2])
