from enum import Enum
from random import randint

from game_board.cell import CellState


class SnakeDirection(Enum):
    UP = 0
    DOWN = 1
    RIGHT = 2
    LEFT = 3


class ServiceError(Exception):
    pass


class GameService:
    """
        The game service
    """
    def __init__(self, board):
        self.__board = board
        self.__snake_direction = SnakeDirection.UP

    @property
    def board(self):
        return self.__board

    @property
    def snake_direction(self):
        return self.__snake_direction

    def search_snake_head(self):
        """
        Searched for the position of the snake's head
        :return: True if the position is found, False else
        """
        for i in range(self.__board.dimension):
            for j in range(self.__board.dimension):
                if self.__board[i][j].state == CellState.HEAD:
                    return i, j
        return None

    def search_snake_body_cells(self):
        """
        Searches for the cells in snake's body
        :return: the list of the body cells if there exist any, None else
        """
        body_cells = []
        for i in range(self.__board.dimension):
            for j in range(self.__board.dimension):
                if self.__board[i][j].state == CellState.BODY:
                    body_cells.append((i, j))
        if not body_cells:
            return None
        return body_cells

    def __validate_cell(self, x, y):
        """
        Validates a cell before trying to move the snake there
        An invalid cell is either not in the board, or already occupied by the snake
        :param x: the x coordinate of the cell
        :param y: the y coordinate of the cell
        :return: True if the cell is valid, False else
        """
        if x < 0 or y < 0 or x >= self.__board.dimension or y >= self.__board.dimension:
            return False
        if self.__board[x][y].state == CellState.HEAD or self.__board[x][y].state == CellState.BODY:
            return False
        return True

    def __is_neighbour(self, x1, y1, x2, y2):
        """
        Checks if 2 cells are neighbours, i.e., their x or y coordinates are equal and the other ones have a difference of
        at one maximum
        """
        if x1 == x2 and abs(y1 - y2) <= 1 or y1 == y2 and abs(x1 - x2) <= 1:
            return True
        return False

    def __move_by_one(self):
        """
        Moves the snake by one square
        :return: True if by making the move the game is over, False else
        """
        head_position = self.search_snake_head()
        body_positions = self.search_snake_body_cells()
        map_direction = {0: (-1, 0), 1: (1, 0), 2: (0, 1), 3: (0, -1)}

        point = map_direction[self.__snake_direction.value]

        self.__board[head_position[0]][head_position[1]].state = CellState.FREE
        if not self.__validate_cell(head_position[0] + point[0], head_position[1] + point[1]):
            return True  # game over

        keep_last_cell = False
        if self.__board[head_position[0] + point[0]][head_position[1] + point[1]].state == CellState.APPLE:
            keep_last_cell = True

        self.__board[head_position[0] + point[0]][head_position[1] + point[1]].state = CellState.HEAD

        last_cell = [head_position[0], head_position[1]]

        index = 0
        while index < len(body_positions):
            for cell in body_positions:
                if self.__is_neighbour(last_cell[0], last_cell[1], cell[0], cell[1]):
                    self.__board[last_cell[0]][last_cell[1]].state = CellState.BODY
                    self.__board[cell[0]][cell[1]].state = CellState.FREE
                    last_cell = [cell[0], cell[1]]
                    body_positions.remove(cell)
                    break
        if keep_last_cell:
            self.__board[last_cell[0]][last_cell[1]].state = CellState.BODY
            self.put_random_apple()
        return False

    def put_random_apple(self):
        """
        Puts a random apple on the board (the apple has to respect the problem statement conditions)
        """
        while True:
            x = randint(0, self.__board.dimension - 1)
            y = randint(0, self.__board.dimension - 1)
            if self.__board[x][y].state != CellState.FREE or self.__board[x][y + 1].state == CellState.APPLE or \
                    self.__board[x][y - 1].state == CellState.APPLE or self.__board[x - 1][
                y].state == CellState.APPLE or \
                    self.__board[x + 1][y].state == CellState.APPLE:
                continue
            self.__board[x][y].state = CellState.APPLE
            return

    def move(self, positions):
        """
        Attemps to make a number of moves on the board
        :param positions: the number of moves
        :return: True if the attempt leads to game over, False else
        """
        game_over = False
        for index in range(positions):
            game_over = self.__move_by_one()
            if game_over:
                return game_over
        return game_over

    def change_direction(self, direction):
        """
        Changes the snake's direction
        :param direction: the new direction
        :return: True if by changing the direction the game ends, False else
        """
        map_direction = {0: SnakeDirection.UP, 1: SnakeDirection.DOWN, 2: SnakeDirection.RIGHT, 3: SnakeDirection.LEFT}
        direction = map_direction[direction]
        if direction == self.__snake_direction:
            return  # cannot move in the same direction

        if (direction, self.__snake_direction) in \
                [(SnakeDirection.UP, SnakeDirection.DOWN), (SnakeDirection.RIGHT, SnakeDirection.LEFT),
                 (SnakeDirection.DOWN, SnakeDirection.UP), (SnakeDirection.LEFT, SnakeDirection.RIGHT)]:
            raise ServiceError('Invalid change of direction.\n')
        self.__snake_direction = direction
        if self.__move_by_one():
            return True
        return False

