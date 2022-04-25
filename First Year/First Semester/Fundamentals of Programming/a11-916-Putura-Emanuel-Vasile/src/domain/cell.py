from dataclasses import dataclass
from enum import Enum


class CellState(Enum):
    """
    Enum class containing the four possible states of a cell
    """
    FREE_CELL = 0
    BLOCKED_CELL = 1
    X_OCCUPIED_CELL = 2
    O_OCCUPIED_CELL = 3
    TEMPORARILY_OCCUPIED_CELL = 4


@dataclass
class Cell:
    """
    Abstract representation of a board cell
        Note that a cell does not actually keep any certain value (e.g., an integer representing a code for the cell value). It
    makes use of the CellState enum class, keeping only the state of the cell (i.e., a value from the enum representing the current
    state of the cell)
    """
    state: CellState = CellState.FREE_CELL  # default state of a cell

    def move_X(self):
        """
        Change the state of the cell - put X in the cell
        """
        self.state = CellState.X_OCCUPIED_CELL

    def move_O(self):
        """
        Change the state of the cell - put O in the cell
        """
        self.state = CellState.O_OCCUPIED_CELL

    def free(self):
        """
        Change the state of the cell - free the cell
        """
        self.state = CellState.FREE_CELL

    def block(self):
        """
        Change the state of the cell - block the cell
        """
        self.state = CellState.BLOCKED_CELL

    def __str__(self):
        """
        Gets the string representation of a cell object - its value
        :return: string - the representation of a cell object
        """
        # state_representation - dictionary mapping the enum values with the corresponding string representations
        state_representation = {0: '', 1: '#', 2: 'X', 3: 'O', 4: 'err'}
        return state_representation[self.state.value]
