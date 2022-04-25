from enum import Enum

import pygame


class CellConstants(Enum):
    """
    Enum class containing all the custom cell constants used in this module
    """
    BLACK_COLOR = (0, 0, 0)
    BLOCKED_COLOR = (155, 165, 165)
    MARGIN_SHRINK_FACTOR = 25


class GUICell(pygame.sprite.Sprite):
    """
    Abstract representation of a GUI cell
    Inherits from pygame.sprite.Sprite class
    """
    def __init__(self, main_surface, position, dimension, color):
        super(GUICell, self).__init__()
        self.__main_surface = main_surface
        self.__surface = pygame.Surface((dimension, dimension))
        self.__surface.fill(color)
        self.__color = color
        self.__rectangle = self.__surface.get_rect(left=position[0], top=position[1])

    def draw(self):
        """
        Draws the cell and its margins
        """
        self.__draw_cell()
        self.__draw_margin()

    def move_X(self):
        """
        Draws X on the cell
        """
        pygame.draw.line(self.__surface, CellConstants.BLACK_COLOR.value, (0, 0), (self.__surface.get_width(), self.__surface.get_height()), 7)
        pygame.draw.line(self.__surface, CellConstants.BLACK_COLOR.value, (0, self.__surface.get_height()), (self.__surface.get_width(), 0), 7)

    def move_O(self):
        """
        Draws O on the cell
        """
        CIRCLE_CENTER = (self.__surface.get_width() / 2, self.__surface.get_height() / 2)
        pygame.draw.circle(self.__surface, CellConstants.BLACK_COLOR.value, CIRCLE_CENTER, self.__surface.get_width() / 2, 5)

    def block(self):
        """
        Draws a blockade on the cell
        """
        self.__surface.fill(CellConstants.BLOCKED_COLOR.value)

    def free(self):
        """
        Frees the cell by redrawing it, using the default cell color
        """
        self.__surface.fill(self.__color)

    def __draw_cell(self):
        """
        Draws the cell on the surface
        """
        self.__main_surface.blit(self.__surface, self.__rectangle)

    def __draw_margin(self):
        """
        Draws the margins of the cell
        """
        HORIZONTAL_MARGIN_WIDTH = self.__surface.get_width()
        HORIZONTAL_MARGIN_HEIGHT = self.__surface.get_height() / CellConstants.MARGIN_SHRINK_FACTOR.value
        VERTICAL_MARGIN_WIDTH = self.__surface.get_width() / CellConstants.MARGIN_SHRINK_FACTOR.value
        VERTICAL_MARGIN_HEIGHT = self.__surface.get_height()
        BLACK_COLOR = (0, 0, 0)

        top_left_corners = {'N': (0, 0), 'E': (self.__surface.get_width() - VERTICAL_MARGIN_WIDTH, 0),
                            'S': (0, self.__surface.get_height() - HORIZONTAL_MARGIN_HEIGHT), 'W': (0, 0)}
        dimensions = {'N': (HORIZONTAL_MARGIN_WIDTH, HORIZONTAL_MARGIN_HEIGHT),
                            'E': (VERTICAL_MARGIN_WIDTH, VERTICAL_MARGIN_HEIGHT),
                            'S': (HORIZONTAL_MARGIN_WIDTH, HORIZONTAL_MARGIN_HEIGHT),
                            'W': (VERTICAL_MARGIN_WIDTH, VERTICAL_MARGIN_HEIGHT)}
        for direction in top_left_corners:
            corner_point = top_left_corners[direction]
            dimension = dimensions[direction]
            pygame.draw.rect(self.__surface, BLACK_COLOR, pygame.Rect(corner_point[0], corner_point[1], dimension[0], dimension[1]))
