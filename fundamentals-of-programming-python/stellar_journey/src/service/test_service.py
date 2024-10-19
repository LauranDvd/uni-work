from unittest import TestCase

from src.domain.board import Board
from src.service.service import Service


class TestService(TestCase):
    def setUp(self) -> None:
        self.board = Board()
        self.service = Service(self.board)

    def tearDown(self) -> None:
        del self.board
        del self.service

    def test__generate_stars(self):
        for _ in range(15):
            self.service._generate_stars(10)  # we only care for n=10

            cnt = 0  # check 10
            for i in range(self.board.lins):
                for j in range(self.board.cols):
                    if self.board._matr[i][j].val == 'star':
                        cnt += 1
            self.assertEqual(cnt, 10)

            # check no neighbors
            dl = [-1, -1, 0, 1, 1, 1, 0, -1]
            dc = [0, 1, 1, 1, 0, -1, -1, -1]
            for i in range(self.board.lins):
                for j in range(self.board.cols):
                    for dir in range(8):
                        new_lin = i + dl[dir]
                        new_col = j + dc[dir]
                        if not (0 <= new_lin < self.board.lins and 0 <= new_col < self.board.cols):
                            continue
                        if self.board._matr[new_lin][new_col] == 'star':
                            self.fail()

            # clean
            for i in range(self.board.lins):
                for j in range(self.board.cols):
                    self.board._matr[i][j].val = 'nothing'
