from src.strategy.strategy import Strategy
from domain.cell import CellState
from random import randint


class BeginnerStrategy(Strategy):
    """
    Abstract representation of the computer's beginner strategy

    Purpose:
        The computer player should move to win the game whenever possible and should block the human player’s
        attempts at 1-move victory, whenever possible. If none of the above cases is present, then the computer
        player takes a valid random move

    Take into consideration the fact that TEMPORARILY_OCCUPIED cell state is used, which basically means that
    such a cell is occupied only during the below algorithms in order to check certain cases (e.g., checking if
    the computer player can make a single move in order to win the game)
    """
    def move(self, board):
        """
        Return a cell for a game move, using the beginner game strategy described above
        :param board: the game board
        :return: a random cell for a game move
        """
        winning_move = self.attempt_winning_move(board)
        if winning_move:
            return winning_move
        possible_moves = self.attempt_defensive_move(board)
        if possible_moves:
            return self.make_random_move(board, possible_moves)
        return self.make_random_move(board, self._get_free_points(board))

    def make_random_move(self, board, possible_moves):
        """
        Makes a random move on the board, selecting it from a list of given possible moves
        :param board: the game board
        :param possible_moves: a list of possible moves
        :return: the random move
        """
        return possible_moves[randint(0, len(possible_moves) - 1)]

    def attempt_winning_move(self, board, default_temp_moves=[]):
        """
        Attempts to make a winning move, if possible. Temporarily occupies certain cells and check
        if the computer player wins by doing such a move
        :param board: the game board
        :param default_temp_moves: already made temporarily moves, which should not be eliminated during
        this function's execution
        :return: a point, if a winning move exits, None else
        """
        for point in self._get_free_points(board):
            if board[point.x][point.y].state == CellState.FREE_CELL:
                self.temporarily_moves(board, [point] + default_temp_moves)
                if not len(self._get_free_points(board)):
                    self.free_temporary_occupations(board)
                    return point
                self.free_temporary_occupations(board)
        return None

    def attempt_defensive_move(self, board):
        """
        Attempts to make a defensive move (i.e., block the human player’s attempts at 1-move victory, if possible)
        :param board: the game board
        :return: the list of possible moves that do not let the other player win next round or None if such moves do
        not exist
        """
        possible_moves = []
        for point in self._get_free_points(board):
            if not self.attempt_winning_move(board, [point]):
                possible_moves.append(point)
            self.free_temporary_occupations(board)
        return None if possible_moves == [] else possible_moves

    def temporarily_moves(self, board, points):
        """
        Makes temporarily moves (i.e., the moves will be deleted at a certain moment in future, before displaying them to
        the user
        :param board: the game board
        :param points: the points where the move will be made
        """
        directions = [-1, 0, 1]  # directions where blockades are attempted
        for point in points:  # for each attempted move
            for row_dir in directions:
                for column_dir in directions:
                    if point.x + row_dir in range(board.rows) and point.y + column_dir in range(board.columns) \
                            and board[point.x + row_dir][point.y + column_dir].state == CellState.FREE_CELL:
                        board[point.x + row_dir][point.y + column_dir].state = CellState.TEMPORARILY_OCCUPIED_CELL

    def free_temporary_occupations(self, board):
        """
        Deletes the temporarily moves (i.e., changes the state of the TEMPORARILY_OCCUPIED cells into FREE state)
        :param board: the game board
        """
        for row in range(board.rows):
            for column in range(board.columns):
                if board[row][column].state == CellState.TEMPORARILY_OCCUPIED_CELL:
                    board[row][column].state = CellState.FREE_CELL
