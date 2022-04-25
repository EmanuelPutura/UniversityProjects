from dataclasses import dataclass
from enum import Enum


class CellState(Enum):
    FREE = 0
    PLAYER_SHIP = 1
    COMPUTER_SHIP = 2
    MISSED = 3
    HIT = 4


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

    def place_player_ship(self):
        """
        Places a human ship in the cell
        """
        self.state = CellState.PLAYER_SHIP

    def place_computer_ship(self):
        """
        Places a computer ship in the cell
        """
        self.state = CellState.COMPUTER_SHIP

    def __str__(self):
        state_representation = {0: '.', 1: '+', 2: '#', 3: 'o', 4: 'X'}
        return state_representation[self.state.value]
