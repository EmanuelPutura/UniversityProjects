from dataclasses import dataclass
from enum import Enum


class CellState(Enum):
    FREE = 0
    APPLE = 1
    HEAD = 2
    BODY = 3


@dataclass
class Cell:
    """
    Represents a board cell
    """
    state: CellState = CellState.FREE

    def free(self):
        """
        Frees the cell
        """
        self.state = CellState.FREE

    def place_apple(self):
        """
        Places an apple in the cell
        """
        self.state = CellState.APPLE

    def place_snake_head(self):
        """
        Places the snake's head in the cell
        """
        self.state = CellState.HEAD

    def place_snake_body(self):
        """
        Places a piece of the snake's body in the cell
        """
        self.state = CellState.BODY

    def __str__(self):
        state_representation = {0: ' ', 1: '.', 2: '*', 3: '+'}
        return state_representation[self.state.value]
