import unittest

from texttable import Texttable

from board.board import Board
from domain.cell import CellState


class TestBoard(unittest.TestCase):
    def setUp(self):
        self.__board = Board()

    def test_rows(self):
        self.assertEqual(self.__board.rows, 6)

    def test_columns(self):
        self.assertEqual(self.__board.columns, 6)

    def test_getitem(self):
        for row in range(self.__board.rows):
            for column in range(self.__board.columns):
                self.assertEqual(self.__board[row][column].state, CellState.FREE_CELL)

    def test_str(self):
        representation = Texttable()
        header = [''] + [chr(ord('A') + index) for index in range(self.__board.columns)]
        representation.header(header)
        for row in range(self.__board.rows):
            row_data = [str(row + 1)] + ['' for column in range(self.__board.columns)]
            representation.add_row(row_data)
        self.assertEqual(str(self.__board), representation.draw())
