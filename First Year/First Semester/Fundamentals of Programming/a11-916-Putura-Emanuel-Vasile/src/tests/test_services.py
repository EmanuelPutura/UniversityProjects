import unittest

from board.board import Board
from domain.cell import CellState
from domain.point import Point
from services.game_service import GameService, CoordinatesError
from strategy.beginner_strategy import BeginnerStrategy


class TestGameService(unittest.TestCase):
    def setUp(self):
        self.__game = GameService(Board(), BeginnerStrategy())

    def test_move(self):
        point = Point(0, 0)
        h_symbol = 'X'
        c_symbol = 'O'
        board = self.__game.board
        self.__game.human_move(h_symbol, point)

        blockades = [(0, 1), (1, 1), (1, 0)]
        for row in range(board.rows):
            for column in range(board.columns):
                if not row and not column:
                    self.assertEqual(board[row][column].state, CellState.X_OCCUPIED_CELL)
                elif (row, column) in blockades:
                    self.assertEqual(board[row][column].state, CellState.BLOCKED_CELL)
                else:
                    self.assertEqual(board[row][column].state, CellState.FREE_CELL)

        point = Point(-1, 0)  # invalid point
        self.assertRaises(CoordinatesError, self.__game.human_move, h_symbol, point)
        try:
            self.__game.human_move(h_symbol, point)
        except CoordinatesError as ce:
            self.assertEqual('CoordinatesError: Invalid coordinates.\n', str(ce))
        point = Point(1, 1)  # blocked point
        self.assertRaises(CoordinatesError, self.__game.human_move, h_symbol, point)
        self.__game.computer_move(c_symbol)
        cnt = 0
        for row in range(board.rows):
            for column in range(board.columns):
                if board[row][column].state == CellState.O_OCCUPIED_CELL:
                    cnt += 1
        self.assertEqual(cnt, 1)
