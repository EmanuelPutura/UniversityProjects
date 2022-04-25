from src.strategy.strategy import Strategy
from domain.cell import CellState
from domain.point import Point
from random import randint


class RandomStrategy(Strategy):
    """
    Abstract representation of the computer's random strategy

    Purpose:
        Make random moves on the game table, without taking into consideration possible advantages (e.g., winning by
        making a certain move)
    """
    def move(self, board):
        """
        Return a random cell for a game move, considering the fact that the cell must be in FREE state
        :param board: the game board
        :return: a random cell for a game move
        """
        x = randint(0, board.rows - 1)
        y = randint(0, board.columns - 1)
        while board[x][y].state != CellState.FREE_CELL:
            x = randint(0, board.rows - 1)
            y = randint(0, board.columns - 1)
        return Point(x, y)
