from texttable import Texttable

from game_board.cell import Cell


class Board:
    """
        The game board
    """
    def __init__(self, rows=6, columns=6):
        self.__rows = rows
        self.__columns = columns
        self.__board = self.__create_board()

    @property
    def rows(self):
        return self.__rows

    @property
    def columns(self):
        return self.__columns

    def __create_board(self):
        """
        Creates the game board (basically a matrix)
        :return: a matrix representing the game board
        """
        return [[Cell() for j in range(self.__columns)] for i in range(self.__rows)]

    def __getitem__(self, key):
        return self.__board[key]

    def __str__(self):
        """
        Gets the string representation of the board
        """
        representation = Texttable()
        header = [''] + [chr(ord('A') + index) for index in range(self.__columns)]
        representation.header(header)

        for row in range(self.__rows):
            row_data = [str(row)] + [self.__board[row][column] for column in range(self.__columns)]
            representation.add_row(row_data)
        return representation.draw()
