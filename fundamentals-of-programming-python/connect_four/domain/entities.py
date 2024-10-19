class Cell:
    def __init__(self):
        self._value = "nothing"

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, val):
        self._value = val

    def is_empty(self):
        return self._value == "nothing"


class Board:
    def __init__(self, lines, cols):
        self._lines = lines
        self._cols = cols
        self._matrix = [[Cell() for _ in range(cols)] for __ in range(lines)]

    @property
    def lines(self):
        return self._lines
    
    @property
    def cols(self):
        return self._cols

    def get_cell(self, lin, col):
        return self._matrix[lin][col]

    def set_cell(self, lin, col, val):
        self._matrix[lin][col].value = val

    def is_inside(self, line, col):
        """
        Is a position inside the board?
        :param line: int
        :param col: int
        :return: True or False
        """
        return 0 <= line < self._lines and 0 <= col < self._cols

    def is_full(self):
        """
        Is the board full?
        :return: True or False
        """
        for i in range(self._lines):
            for j in range(self._cols):
                if self._matrix[i][j].is_empty():
                    return False
        return True

    def is_cell_free(self, line, col):
        """
        Is a cell free?
        :param line: int between 0 and self._lines-1
        :param col: int between 0 and self._cols-1
        :return: True or False
        """
        return self._matrix[line][col].is_empty()
