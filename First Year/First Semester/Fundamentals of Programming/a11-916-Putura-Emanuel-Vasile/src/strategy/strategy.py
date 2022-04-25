from abc import abstractmethod
from domain.cell import CellState
from domain.point import Point


class Strategy:
    """
    Base strategy class dealing with computer's next move and its strategies
    """
    @abstractmethod
    def move(self, *args):
        """
        Abstract method that performs computer's next move
        """
        pass

    def _get_free_points(self, board):
        """
        Gets all the free points/cells in the board (i.e., the cell is in FREE state)
        :param board: the game board
        :return: all free points/cells in the board
        """
        return [Point(x, y) for x in range(board.rows) for y in range(board.columns) if board[x][y].state == CellState.FREE_CELL]
