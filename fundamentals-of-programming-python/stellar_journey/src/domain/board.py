from src.domain.cell import Cell


class Board:
    def __init__(self, lins=8, cols=8):
        self._lins = lins
        self._cols = cols
        self._matr = [[Cell('nothing') for j in range(cols)] for i in range(lins)]

    @property
    def lins(self):
        return self._lins

    @property
    def cols(self):
        return self._cols

    def get_cell(self, lin, col):
        """
        Get cell at position (lin, col)
        :param lin: int -- valid line on the board
        :param col: int -- valid column on the board
        :return: Cell object -- the cell at (lin, col)
        """
        return self._matr[lin][col]

    def set_cell(self, lin, col, val):
        """
        Set the cell at given position to given value
        :param lin: int -- valid line on the board
        :param col: int -- valid column on the board
        :param val: str -- either 'nothing' or 'endeavor' or 'cruiser' or 'star'
        """
        self._matr[lin][col].val = val

    def no_cruisers(self):
        number = 0
        for i in range(self._lins):
            for j in range(self._cols):
                if self._matr[i][j].val == 'cruiser':
                    number += 1
        return number
