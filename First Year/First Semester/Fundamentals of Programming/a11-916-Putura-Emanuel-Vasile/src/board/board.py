from enum import Enum

from texttable import Texttable

from iterator.collection import Collection
from domain.cell import Cell


class DefaultBoardDimensions(Enum):
    """
    Enum class used for storing the default board dimensions
    """
    ROWS = 6
    COLUMNS = 6


class Board:
    """
    Abstract representation of a services board
    """
    def __init__(self, rows=DefaultBoardDimensions.ROWS.value, columns=DefaultBoardDimensions.COLUMNS.value):
        self.__rows = rows
        self.__columns = columns
        self.__data = self.__create_board()

    @property
    def rows(self):
        return self.__rows

    @property
    def columns(self):
        return self.__columns

    def __create_board(self):
        """
        Creates the services board based on the __rows and __columns class attributes
        :return: a services board of dimensions __rows x __columns populated with the value from
        the __empty_value class attribute
        """
        return Collection([Collection([Cell() for column in range(self.__columns)]) for row in range(self.__rows)])

    def __getitem__(self, key):
        """
        Returns the list __data[key] representing the no. key row in the __data matrix
        """
        return self.__data[key]

    def __str__(self):
        """
        The string representation of a Board object
        """
        representation = Texttable()
        header = [''] + [chr(ord('A') + index) for index in range(self.__columns)]
        representation.header(header)

        for row in range(self.__rows):
            # the default cell empty value is None, but I prefer not to print 'None' to the user
            row_data = [str(row + 1)] + [self.__data[row][column] for column in range(self.__columns)]
            representation.add_row(row_data)
        return representation.draw()
