from domain.cell import CellState
from domain.point import Point


class ServiceGameError(Exception):
    """
    Custom exception class representing a service game error
    """
    def __init__(self, message):
        self._messagge = message

    def __str__(self):
        return self._messagge


class CoordinatesError(ServiceGameError):
    """
    Custom exception class representing a coordinates error
    """
    pass


class GameService:
    """
    Service class of the game
    """
    def __init__(self, board, strategy):
        self.__board = board
        self.__strategy = strategy

    @property
    def board(self):
        return self.__board

    def __game_over(self):
        """
        Checks whether the game is over or not
        :return: true if the game is over, false else
        """
        return not CellState.FREE_CELL in [cell.state for row in range(self.__board.rows) for cell in self.__board[row]]

    def __get_cell_state(self, point):
        """
        Gets the state of the cell having the given coordinates
        :param point: the coordinates of the cell
        :return: the state of the cell having the given coordinates
        """
        return self.__board[point.x][point.y].state

    def __validate_move(self, point):
        """
        Validates a move
        :param point: the coordinates of the move
        :raises: CoordinatesError if the move is invalid
        """
        if point.x not in range(self.__board.rows) or point.y not in range(self.__board.columns):
            raise CoordinatesError('CoordinatesError: Invalid coordinates.\n')
        if not self.__get_cell_state(point) == CellState.FREE_CELL:
            raise CoordinatesError('CoordinatesError: Cell already occupied.\n')

    def __populate_blockades(self, point):
        """
        Blocks the cell around a given point and returns the number of blocked cells
        :param point: the given point
        :return: the number of blocked cells
        """
        blocked_cells = 0  # the number of blocked cells
        directions = [-1, 0, 1]  # directions where blockades are attempted
        for row_dir in directions:
            for column_dir in directions:
                if point.x + row_dir in range(self.__board.rows) and point.y + column_dir in range(self.__board.columns) \
                        and Point(0, 0) != Point(row_dir, column_dir):
                    self.__board[point.x + row_dir][point.y + column_dir].state = CellState.BLOCKED_CELL
                    blocked_cells += 1
        return blocked_cells

    def human_move(self, value, point):
        """
        Attempts to make a human move
        :param value: the player string symbol (can be 'X' or 'O')
        :param point: the coordinates of the attempted move
        :return: true if the game is over after the move, false else
        """
        # dictionary that maps a player string symbol to a corresponding cell state when attempting a move on the board
        state_dict = {'X': CellState.X_OCCUPIED_CELL, 'O': CellState.O_OCCUPIED_CELL}
        self.__validate_move(point)  # validate the attempted move
        self.__board[point.x][point.y].state = state_dict[value]  # take the move
        self.__populate_blockades(point)  # block the cells around the latest occupied cell
        return self.__game_over()  # check if the game is over - if true, then human wins

    def computer_move(self, value):
        """
        Attempts to make a computer move
        :param value: the computer string symbol (can be 'X' or 'O')
        :return: true if the game is over after the move, false else
        """
        # dictionary that maps a player string symbol to a corresponding cell state when attempting a move on the board
        state_dict = {'X': CellState.X_OCCUPIED_CELL, 'O': CellState.O_OCCUPIED_CELL}
        point = self.__strategy.move(self.__board)
        x = point.x
        y = point.y
        self.__board[x][y].state = state_dict[value]  # take the move
        self.__populate_blockades(Point(x, y))  # block the cells around the latest occupied cell
        return self.__game_over()  # check if the game is over - if true, then computer wins
