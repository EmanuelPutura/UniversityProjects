import unittest

from domain.point import Point
from src.board.board import Board
from domain.cell import Cell, CellState
from strategy.beginner_strategy import BeginnerStrategy
from strategy.minimax_strategy import MinimaxStrategy, MinimaxResults
from strategy.random_strategy import RandomStrategy


class TestBeginnerStrategy(unittest.TestCase):
    def setUp(self):
        self.__strategy = BeginnerStrategy()
        self.__board = Board()

        self.__board[1][1] = self.__board[4][1] = Cell(CellState.X_OCCUPIED_CELL)
        self.__board[1][4] = self.__board[3][3] = Cell(CellState.O_OCCUPIED_CELL)
        free_cells = [(5, 3), (5, 4), (5, 5), (4, 5), (3, 5)]
        for row in range(self.__board.rows):
            for column in range(self.__board.columns):
                if (row, column) not in free_cells and self.__board[row][column].state == CellState.FREE_CELL:
                    self.__board[row][column].state = CellState.BLOCKED_CELL

    def test_attempt_defensive_move(self):
        self.assertEqual(self.__strategy.move(self.__board), Point(5, 5))

    def test_attempt_winning_move(self):
        self.__board[3][5].state = CellState.X_OCCUPIED_CELL
        self.__board[4][5].state = CellState.BLOCKED_CELL
        self.assertEqual(self.__strategy.attempt_winning_move(self.__board), Point(5, 4))
        self.__board[3][5].state = self.__board[4][5].state = CellState.FREE_CELL

    def test_move(self):
        self.__board[3][5].state = CellState.X_OCCUPIED_CELL
        self.__board[4][5].state = CellState.BLOCKED_CELL
        self.assertEqual(self.__strategy.move(self.__board), Point(5, 4))
        self.__board = Board()
        for row in range(self.__board.rows):
            for column in range(self.__board.columns):
                if (row, column) != (0, 0) and (row, column) != (5, 5):
                    self.__board[row][column].state = CellState.BLOCKED_CELL
        random_point = self.__strategy.move(self.__board)
        self.assertEqual(self.__board[random_point.x][random_point.y].state, CellState.FREE_CELL)


class TestRandomStrategy(unittest.TestCase):
    def setUp(self):
        self.__board = Board(2, 2)
        self.__board[0][1].state = self.__board[1][0].state = self.__board[1][1].state = CellState.BLOCKED_CELL
        self.__strategy = RandomStrategy()

    def test_random_strategy(self):
        self.assertEqual(self.__strategy.move(self.__board), Point(0, 0))


class TestMinimaxStrategy(unittest.TestCase):
    def setUp(self):
        self.__board = Board()
        for row in range(self.__board.rows):
            for column in range(self.__board.columns):
                self.__board[row][column].state = CellState.BLOCKED_CELL

        # build a special case and test it
        self.__board[0][1].state = self.__board[1][0].state = self.__board[1][1].state = self.__board[1][2].state \
                                    = self.__board[2][0].state = CellState.FREE_CELL

        self.__minimax_strategy = MinimaxStrategy()

    def test_move(self):
        move = self.__minimax_strategy.move(self.__board)
        self.assertEqual(move, Point(1, 1))

    def test_attempt_impossible_move(self):
        # add default temporary moves and attemp to move there (the cell is blocked)
        self.__minimax_strategy = MinimaxStrategy([Point(0, 0)])
        self.assertEqual(False, self.__minimax_strategy.attempt_move(self.__board))

    def test_minimax_for_high_possible_depth(self):
        for row in range(self.__board.rows):
            for column in range(self.__board.columns):
                self.__board[row][column].state = CellState.BLOCKED_CELL
        self.__board[0][0].state = CellState.FREE_CELL  # only one possible move on the board

        # suppose we arrived in this situation with depth = 3 => even if the score for this move should be
        # maximum as maximizer wins this round, it will be the NONE value from the MinimaxResults enum class,
        # because the algorithm does not accept a greater depth than 2
        score = self.__minimax_strategy.minimax(self.__board, 3, True)
        self.assertEqual(score, MinimaxResults.NONE.value)

    def test_minimax_always_winning_option(self):
        for row in range(self.__board.rows):
            for column in range(self.__board.columns):
                self.__board[row][column].state = CellState.BLOCKED_CELL
        self.__board[0][0].state = CellState.FREE_CELL  # only one possible move on the board

        score = self.__minimax_strategy.minimax(self.__board, 0, True)
        self.assertEqual(MinimaxResults.MINIMIZER.value, score)

    def test_minimax_always_losing_option(self):
        self.__board[3][3].state = self.__board[4][4].state = self.__board[3][4].state = self.__board[4][3].state = CellState.FREE_CELL
        score = self.__minimax_strategy.minimax(self.__board, 0, True)
        self.assertEqual(score, MinimaxResults.MAXIMIZER.value, score)
