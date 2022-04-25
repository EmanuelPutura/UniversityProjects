from src.strategy.strategy import Strategy
from domain.cell import CellState
from enum import Enum
import sys


class MinimaxResults(Enum):
    """
    Enum class containing constants used in the Minimax Algorithm implementation
    """
    MAXIMIZER = sys.maxsize
    MINIMIZER = -sys.maxsize
    NONE = 0
    SCORE_INCREMENT = 1


class MinimaxStrategy(Strategy):
    """
    Abstract representation of one of the computer's strategies: the Minimax Strategy
    This strategy involves checking all (or almost all) the possible ways the game can turn around and chose the best move for the computer, considering
    that the human player plays optimally too.

    Maximizer <---> Minimizer
    The first one needs high scores, the second one small scores
    Consider the game state as being represented by a graph - each move is equivalent to a in-depth move in the graph, the move being chosen
    accordingly to the higher/smaller score (depending if the move is made by the maximizer or by the minimizer) saved in the graph nodes
    """
    def __init__(self, temporarily_occupied_cells=[]):
        # contains the cells that are temporarily occupied during the algorithm
        self.__temporarily_occupied_cells = temporarily_occupied_cells

    def move(self, board):
        """
        Makes a move on the board. The move is supposed to be the best possible move, being given the current state of the board
        """
        free_points = self._get_free_points(board)
        best_score = MinimaxResults.MINIMIZER.value
        best_move = None

        for point in free_points:
            self.__temporarily_occupied_cells.append(point)
            score = self.minimax(board, 0, True)
            self.__temporarily_occupied_cells.remove(point)
            if score >= best_score:
                best_score = score
                best_move = point
        return best_move

    def attemp_winning(self, board):
        """
        Checks if the game is won, taking into consideration the temporarily moves too
        :param board: the current game board
        :returns: True if a winner can be decided, False else
        """
        free_points = self._get_free_points(board)
        for point in free_points:
            blocked = False  # checks if a temporarily blockade has been placed here
            for temporarily_cell in self.__temporarily_occupied_cells:
                if -1 <= temporarily_cell.x - point.x <= 1 and -1 <= temporarily_cell.y - point.y <= 1:
                    blocked = True
                    break
            if not blocked:
                return False
        return True

    def attempt_move(self, board):
        """
        Attempts to make a move on the board. The attempted move is a temporily one and is saved into the temporarily_occupied_cells attribute of the class
        (as the last item of this list)
        :param board: the current game board
        :returns: True if the move can be done, False else
        """
        attempted_move = self.__temporarily_occupied_cells[-1]
        if board[attempted_move.x][attempted_move.y].state != CellState.FREE_CELL:
            return False
        for cell in self.__temporarily_occupied_cells[:-1]:
            if -1 <= cell.x - attempted_move.x <= 1 and -1 <= cell.y - attempted_move.y <= 1:
                return False
        return True

    def minimax(self, board, depth, maximizer):
        """
        Implementation of the Minimax Algorithm
        Note that the minimax current score (or maybe better the maximum 'efficiency' of a move from the current game situation) is computed
        in the general case by additions/subtractions of a certain (almost) randomly chosen value saved in the MinimaxResults Enum class
        :param board: the game board
        :param depth: the depth in the 'graph of the algorithm' - basically the number of in-advance moves performed
        :param maximizer: True if it's maximizer turn, False else
        :returns: the minimax best current score
        """
        if depth > 2:  # because of time complexity reasons the algorithm is limited to a maximum depth of 2
            return MinimaxResults.NONE.value

        if self.attemp_winning(board):  # attempt to win the game with the current temporary moves
            return MinimaxResults.MAXIMIZER.value

        free_points = self._get_free_points(board)
        in_depth_scores = []  # these are all the possible scores obtainable by making a move
        for point in free_points:
            self.__temporarily_occupied_cells.append(point)
            if not self.attempt_move(board):
                self.__temporarily_occupied_cells.remove(point)
                continue
            in_depth_scores.append(-self.minimax(board, depth + 1, not maximizer))
            self.__temporarily_occupied_cells.remove(point)

        maxim_score = MinimaxResults.MINIMIZER.value
        minim_score = MinimaxResults.MAXIMIZER.value

        # compute the maximum/minimum score (return maximum if it's maximizer's turn, else minimum)
        for score in in_depth_scores:  # we compute both the maximum and minimum score and decide later which one is needed
            if score < minim_score:
                minim_score = score
            if score > maxim_score:
                maxim_score = score
        # if it's maximizer's turn maximum score achievable is returned, else the minimum one
        return maxim_score if maximizer else minim_score
