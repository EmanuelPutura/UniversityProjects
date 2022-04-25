from enum import Enum

import pygame

from domain.cell import CellState
from presentation.GUI.gui_cell import GUICell


class BoardConstants(Enum):
    """
    Enum class containing the custom board constants used in this module
    """
    BLACK_COLOR = (0, 0, 0)
    BOARD_SIDE = 6
    MARGIN_WIDTH = 3


class GUIBoard(pygame.sprite.Sprite):
    """
    Abstract representation of the GUI game board
    Inherits from pygame.sprite.Sprite class
    """
    def __init__(self, main_window, position, dimension, cell_color, side=BoardConstants.BOARD_SIDE.value):
        super(GUIBoard, self).__init__()
        self.__main_window = main_window
        self.__surface = pygame.Surface((dimension, dimension))
        self.__cell_color = cell_color
        self.__rectangle = self.__surface.get_rect(left=position[0], top=position[1])
        self.__side = side
        self.__gui_board = self.__init_board_cells()

    @property
    def side(self):
        return self.__side

    def __init_board_cells(self):
        """
        Initializes the boards cells (implies building the gui_board that contains all the board cells)
        """
        CELL_SIDE = self.__surface.get_height() / self.__side
        board = []
        for row in range(self.__side):
            board.append([])
            for column in range(self.__side):
                board[row].append(GUICell(self.__surface, (CELL_SIDE * row, CELL_SIDE * column), CELL_SIDE, self.__cell_color))
        return board

    def draw(self):
        """
        Draws all the cells in the board and the whole board on the main window
        """
        for row in range(self.__side):
            for column in range(self.__side):
                self.__gui_board[row][column].draw()
        self.__main_window.blit(self.__surface, self.__rectangle)

    def update_board(self, board):
        """
        Updates the board (in case a player move is made)
        """
        for row in range(board.rows):
            for column in range(board.columns):
                state_dict = {CellState.X_OCCUPIED_CELL: self.__gui_board[row][column].move_X, CellState.O_OCCUPIED_CELL: self.__gui_board[row][column].move_O,
                              CellState.FREE_CELL: self.__gui_board[row][column].free, CellState.BLOCKED_CELL: self.__gui_board[row][column].block}
                state_dict[board[row][column].state]()
