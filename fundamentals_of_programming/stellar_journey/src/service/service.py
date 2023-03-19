import random

from src.service.service_error import MoveError


class Service:
    def __init__(self, board):
        self._board = board

    def _neighbor_endeavor(self, lin, col):
        dl, dc = Service._get_directions()
        for dir in range(8):
            new_lin = lin + dl[dir]
            new_col = col + dc[dir]
            if self._valid_pos(new_lin, new_col) and self._board.get_cell(new_lin, new_col).val == 'endeavor':
                return True
        return False

    def get_cell_nice(self, lin, col, cheat=False):
        # aka the way it will be printed
        trans = {'endeavor': 'E', 'star': '*', 'cruiser': 'B', 'nothing': ''}

        cell = self._board.get_cell(lin, col)
        val = cell.val
        if val != 'cruiser':
            return trans[val]

        if self._neighbor_endeavor(lin, col) or cheat:
            return 'B'
        return ''

    @staticmethod
    def _get_directions():
        """
        Return direction vectors (8 directions)
        :return: tuple (dl, dc) where dl, dc are lists of 8 ints
        """
        dl = [-1, -1, 0, 1, 1, 1, 0, -1]
        dc = [0, 1, 1, 1, 0, -1, -1, -1]
        return dl, dc

    def _valid_pos(self, lin, col):
        """
        Is a position valid on the board?
        :param lin: int
        :param col: int
        :return: True -- if (lin, col) is a valid position on the board
                 False -- if it's not
        """
        return 0 <= lin < self._board.lins and 0 <= col < self._board.cols

    def _has_adjacent_stars(self, lin, col):
        """
        Does the cell at a given position either have stars as neighbors (8 directions), or
        is itself a star?
        :param lin: int -- valid line on the board
        :param col: int -- valid line on the board
        :return: True -- if at (lin, col) there's a star, or it neighbors at least one star
                 False -- if at (lin, col) there isn't a star and it doesn't neighbor a star
        """
        if self._board.get_cell(lin, col).val == 'star':
            return True
        dl, dc = Service._get_directions()
        for dir in range(8):
            new_lin = lin + dl[dir]
            new_col = col + dc[dir]
            if self._valid_pos(new_lin, new_col) and self._board.get_cell(new_lin, new_col).val == 'star':
                return True
        return False

    def _generate_stars(self, n=10):
        """
        Randomly place a given number of stars on the board (default=10)
        :param n: int -- the number of stars to be generated
        """
        for _ in range(n):
            lin = random.randint(0, 7)
            col = random.randint(0, 7)
            while self._has_adjacent_stars(lin, col):
                lin = random.randint(0, 7)
                col = random.randint(0, 7)
            self._board.set_cell(lin, col, 'star')

    def _generate_endeavor(self):
        lin = random.randint(0, 7)
        col = random.randint(0, 7)
        while self._board.get_cell(lin, col).val == 'star':
            lin = random.randint(0, 7)
            col = random.randint(0, 7)
        self._board.set_cell(lin, col, 'endeavor')

    def _generate_cruisers(self, n):
        for _ in range(n):
            lin = random.randint(0, 7)
            col = random.randint(0, 7)
            while self._board.get_cell(lin, col).val != 'nothing':
                lin = random.randint(0, 7)
                col = random.randint(0, 7)
            self._board.set_cell(lin, col, 'cruiser')

    def start_game(self):
        self._generate_stars()
        self._generate_endeavor()
        self._generate_cruisers(3)

    @staticmethod
    def char_to_int(x):
        trans = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7}
        return trans[x]

    def _line_has_e(self, line):
        for col in range(8):
            if self._board.get_cell(line, col).val == 'endeavor':
                return True
        return False

    def _col_has_e(self, col):
        for line in range(8):
            if self._board.get_cell(line, col).val == 'endeavor':
                return True
        return False

    def _diag_has_e(self, lin, col):
        dl, dc = Service._get_directions()
        for dir in [1, 3, 5, 7]:
            new_lin, new_col = lin, col
            while self._valid_pos(new_lin, new_col):
                if self._board.get_cell(new_lin, new_col).val == 'endeavor':
                    return True
                new_lin += dl[dir]
                new_col += dc[dir]
        return False

    def _get_e_pos(self):
        for i in range(8):
            for j in range(8):
                if self._board.get_cell(i, j).val == 'endeavor':
                    return i, j

    def _get_dir_path(self, pos1, pos2):
        # pos1...pos2: which direction?
        dl, dc = Service._get_directions()
        for dir in range(8):
            lin, col = pos1
            while self._valid_pos(lin, col):
                if (lin, col) == pos2:
                    return dir
                lin += dl[dir]
                col += dc[dir]

    def _star_in_path(self, pos1, pos2):
        dl, dc = Service._get_directions()
        dir = self._get_dir_path(pos1, pos2)

        lin, col = pos1
        while (lin, col) != pos2:
            if self._board.get_cell(lin, col).val == 'star':
                return True
            lin += dl[dir]
            col += dc[dir]
        return self._board.get_cell(pos2[0], pos2[1]).val == 'star'

    def _move_e(self, lin, col):
        curr_pos = self._get_e_pos()
        self._board.set_cell(curr_pos[0], curr_pos[1], 'nothing')
        self._board.set_cell(lin, col, 'endeavor')

    @staticmethod
    def _pos_str_to_ints(position: str):
        if len(position) != 2:
            raise MoveError("Position should have length 2")
        try:
            lin = Service.char_to_int(position[0])
            col = int(position[1]) - 1
        except KeyError:
            raise MoveError("Line invalid")
        except ValueError:
            raise MoveError("Column invalid")

        if not 0 <= col < 8:
            raise MoveError("Line invalid")
        return lin, col

    def warp(self, position: str) -> bool:
        lin, col = Service._pos_str_to_ints(position)  # might raise MoveError

        # same row/col/diag with E?
        if not self._line_has_e(lin) and not self._col_has_e(col) and not self._diag_has_e(lin, col):
            raise MoveError("Position not on same row/column/diagonal with E")

        # no stars in the way?
        if self._star_in_path(self._get_e_pos(), (lin, col)):
            raise MoveError("There's a star in the way")

        if self._board.get_cell(lin, col).val == 'cruiser':
            return True  # game over

        self._move_e(lin, col)
        return False

    def _erase_cruisers(self):
        for i in range(8):
            for j in range(8):
                if self._board.get_cell(i, j).val == 'cruiser':
                    self._board.set_cell(i, j, 'nothing')

    def _reposition_cruisers(self):
        no_cruisers = self._board.no_cruisers()
        self._erase_cruisers()

        for _ in range(no_cruisers):
            lin = random.randint(0, 7)
            col = random.randint(0, 7)
            while self._board.get_cell(lin, col).val != 'nothing':
                lin = random.randint(0, 7)
                col = random.randint(0, 7)
            self._board.set_cell(lin, col, 'cruiser')

    def fire(self, position: str):
        lin, col = Service._pos_str_to_ints(position)  # may raise MoveError

        if not self._neighbor_endeavor(lin, col):
            raise MoveError("Position not adjacent to E")
        if self._board.get_cell(lin, col).val != 'cruiser':
            raise MoveError("No cruiser there")

        self._board.set_cell(lin, col, 'nothing')
        self._reposition_cruisers()

        return self._board.no_cruisers() == 0
