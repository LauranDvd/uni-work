import random

from domain.entities import Board
from domain.move_error import MoveError


class Service:
    def __init__(self, board: Board):
        self._board = board

    def init_board(self):
        """
        Initialize the board
        """
        for i in range(self._board.lines):
            for j in range(self._board.cols):
                self._board.set_cell(i, j, "nothing")

    @property
    def board_lines(self):
        return self._board.lines

    @property
    def board_cols(self):
        return self._board.cols

    def get_cell_value(self, lin, col):
        """
        The content of a cell
        :param lin: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :return: str ("nothing" or "user" or "computer")
        """
        cell = self._board.get_cell(lin, col)
        return cell.value

    def get_cell_value_nice(self, lin, col):
        """
        The content of a cell, as one character
        :param lin: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :return: str ("." -- free or "x" -- user or "0" -- computer)
        """
        aux = self.get_cell_value(lin, col)
        if aux == "computer":
            return '0'
        elif aux == "user":
            return 'x'
        return '.'

    def _is_lifted(self, line, col):
        """
        Is a cell "lifted"?
        :param line: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :return: True -- if it's on the last line or has something below
                 False -- otherwise
        """
        return line + 1 == self.board_lines or self.get_cell_value(line + 1, col) != "nothing"

    def _is_movable(self, line, col):
        """
        Can the player move here?
        :param line: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :return: True or False
        """
        if not self._board.is_inside(line, col):
            return False
        if not self._board.is_cell_free(line, col):
            return False
        return self._is_lifted(line, col)

    def is_full(self):
        return self._board.is_full()

    def move_user(self, col):
        """
        Record user's move on column [col]
        :param col: integer
        :raises: MoveError -- if the column either doesn't exist or is full
        """
        if not 0 <= col < self.board_cols:
            raise MoveError("Invalid column")
        line = self.board_lines - 1  # find the line
        while line >= 0 and not self._board.is_cell_free(line, col):
            line -= 1

        if line < 0:
            raise MoveError("That column is full")

        self._board.set_cell(line, col, "user")

    def _winning_move(self, lin, col, who):
        """
        Would a player win if they moved in a certain cell?
        :param lin: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :param who: str ("user" or "computer")
        :return: True or False
        """
        self._board.set_cell(lin, col, who)
        answer = self.is_winner()
        self._board.set_cell(lin, col, "nothing")
        return answer

    def _random_move(self):
        """
        Return a random valid move
        :return: pair (line, col)
        """
        line = random.randint(0, self.board_lines - 1)
        col = random.randint(0, self.board_cols - 1)
        while not self._is_movable(line, col):
            line = random.randint(0, self.board_lines - 1)
            col = random.randint(0, self.board_cols - 1)
        return line, col

    def _would_double_attack(self, lin, col, who):
        """
        If player [who] moved in a given cell, would they make a double attack?
        (i.e. afterwards there would be more cells where if they moved they would win)
        :param lin: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :param who: str ("user" or "computer")
        :return: True or False
        """
        if self.get_cell_value(lin, col) != "nothing":
            return False
        self._board.set_cell(lin, col, who)

        winning_cnt = 0
        for i in range(self.board_lines):
            for j in range(self.board_cols):
                if self._is_movable(i, j) and self._winning_move(i, j, who):
                    winning_cnt += 1

        self._board.set_cell(lin, col, "nothing")

        return winning_cnt >= 2

    def _has_neighbor(self, lin, col, what):
        """
        Does a given cell have a neighbor of a given value?
        :param lin: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :param what: str ("user" or "computer" or "nothing")
        :return: True or False
        """
        dl, dc = Service.get_direction_arrays()
        for dir in range(8):
            new_lin, new_col = lin + dl[dir], col + dc[dir]
            if self._board.is_inside(new_lin, new_col) and self.get_cell_value(new_lin, new_col) == what:
                return True
        return False

    def _find_win_block_move(self):
        """
        Searches both for a direct win for the computer, and for a move which
        blocks user's 1-move win (if he has such move)
        :return: tuple of four (line_win, col_win, line_block, col_block) denoting the two cells
                 or (-1, -1) where there isn't such cell
        """
        line_win, col_win = -1, -1
        line_block, col_block = -1, -1
        for i in range(self.board_lines):
            for j in range(self.board_cols):
                if self.get_cell_value(i, j) == "nothing":
                    if self._is_movable(i, j) and self._winning_move(i, j, "computer"):
                        line_win, col_win = i, j
                    if self._is_movable(i, j) and self._winning_move(i, j, "user"):
                        line_block, col_block = i, j
        return line_win, col_win, line_block, col_block

    def _find_double_attack_move(self):
        """
        Find a cell where the computer could make a double attack.
        (i.e. afterwards there would be more cells where if they moved they would win)
        :return: int pair (line, col), denoting the desired cell
                 or (-1, -1) if there isn't such cell
        """
        line_double, col_double = -1, -1
        for i in range(self.board_lines):
            for j in range(self.board_cols):
                if self._is_movable(i, j) and self._would_double_attack(i, j, "computer"):
                    line_double, col_double = i, j
        return line_double, col_double

    def _find_neighboring_move(self):
        """
        Find a cell where the computer could move, such that it neighbors other cell occupied by the computer.
        If possible, it should also neighbor a cell occupied by the user.
        :return: tuple (line_1, col_1, line_2, col_2) denoting two cells which are a valid move.
                 pair (line_1, col_1) is a cell which neighbors a computer's cell
                 pair (line_2, col_2) is a cell which neighbors both a user's and computer's cell.
                 return (-1, -1) where there isn't such cell
        """
        line_neigh, col_neigh = -1, -1
        line_neigh_both, col_neigh_both = -1, -1
        for i in range(self.board_lines):
            for j in range(self.board_cols):
                if self._is_movable(i, j):
                    if self._has_neighbor(i, j, "computer"):
                        line_neigh, col_neigh = i, j
                        if self._has_neighbor(i, j, "user"):
                            line_neigh_both, col_neigh_both = i, j
        return line_neigh, col_neigh, line_neigh_both, col_neigh_both

    def _find_next_move(self):
        """
        What will the computer move?
        :return: int pair (line, col) denoting the position
        """
        # 1, 2) win if it can; if not, block user's win if there is
        line_win, col_win, line_block, col_block = self._find_win_block_move()
        if line_win != -1:
            return line_win, col_win
        if line_block != -1:
            return line_block, col_block

        # 3) double attack
        line_double, col_double = self._find_double_attack_move()
        if line_double != -1:
            return line_double, col_double

        # 4, 5) find cell neighboring both computer's and user's pieces / just computer's
        line_neigh, col_neigh, line_neigh_both, col_neigh_both = self._find_neighboring_move()
        if line_neigh_both != -1:
            return line_neigh_both, col_neigh_both
        if line_neigh != -1:
            return line_neigh, col_neigh

        return self._random_move()

    def computer_move(self):
        """
        Computer moves
        """
        line, col = self._find_next_move()

        self._board.set_cell(line, col, "computer")

    @staticmethod
    def get_direction_arrays():
        dl = [-1, -1, 0, 1, 1, 1, 0, -1]
        dc = [0, 1, 1, 1, 0, -1, -1, -1]
        return dl, dc

    def is_streak_here(self, line, col, dir):
        """
        Starting from a given cell and going in a given direction, do we get 4 cells belonging to the same player?
        :param line: int between 0 and self._board.lines-1
        :param col: int between 0 and self._board.cols-1
        :param dir: integer between 0 and 7
        :return: True or False
        """
        dl, dc = Service.get_direction_arrays()
        line_last = line + dl[dir] * 3
        col_last = col + dc[dir] * 3
        if self._board.is_inside(line_last, col_last):
            line2 = line
            col2 = col
            for it in range(3):
                line2 += dl[dir]
                col2 += dc[dir]
                if self.get_cell_value(line2, col2) != self.get_cell_value(line, col):
                    return False
            return True
        else:
            return False

    def is_winner(self):
        """
        Is there a winner?
        :return: True or False
        """
        for i in range(self.board_lines):
            for j in range(self.board_cols):
                if self.get_cell_value(i, j) != "nothing":
                    for dir in range(1, 5):
                        if self.is_streak_here(i, j, dir):
                            return True
        return False

    def get_special_print_cells(self):
        """
        Which cells which are involved in a streak of 4?
        :return: matrix of booleans having the same size as the board
                 (True for cells which are)
        """
        dl, dc = Service.get_direction_arrays()
        special_print = [[False for _ in range(self.board_cols)] for _2 in range(self.board_lines)]
        for i in range(self.board_lines):
            for j in range(self.board_cols):
                if self.get_cell_value(i, j) != "nothing":
                    for dir in range(4):
                        if self.is_streak_here(i, j, dir):
                            i2 = i
                            j2 = j
                            for it in range(4):
                                special_print[i2][j2] = True
                                i2 += dl[dir]
                                j2 += dc[dir]
        return special_print
