from enum import Enum
import os

import pygame
from pygame.locals import (
    K_ESCAPE,
    KEYDOWN,
    QUIT
)

from domain.point import Point
from presentation.GUI.gui_board import GUIBoard
from presentation.consoleUI.consoleUI import UserInputError
from services.game_service import CoordinatesError, ServiceGameError


class GUIConstants(Enum):
    """
    Enum class containing all the custom constants used in the GUI class
    """
    # dimensions
    SCREEN_WIDTH = 500
    SCREEN_HEIGHT = 500
    BOARD_DIMENSION = 500
    WINNER_FONT_DIM = 40

    # colors
    BACKGROUND_COLOR = (190, 205, 215)
    CELL_COLOR = (215, 215, 215)
    OPTIONAL_TEXT_COLOR = (61, 93, 154)
    TEXT_COLOR = (150, 40, 30)

    # names
    WINDOW_CAPTION = 'Obstruction'

    # time
    END_GAME_TIME_WAIT = 2000


class GUI:
    """
    Main GUI class that implements the GUI. This UI can be chosen from the settings.properties file of the application and it is
    the default UI of the game
    """
    def __init__(self, game, human_symbol, computer_symbol):
        pygame.init()  # initialize pygame
        pygame.display.set_caption(GUIConstants.WINDOW_CAPTION.value)  # set main window name
        relative_path = os.path.dirname(os.path.dirname(os.path.dirname(__file__))) + '\\assets\icon.png'
        programIcon = pygame.image.load(relative_path)  # set the game icon
        pygame.display.set_icon(programIcon)
        self.__game = game  # the game service
        # create the screen object - the size is determined by the constants defined in the GameDimensions enum class
        self.__main_window = pygame.display.set_mode((GUIConstants.SCREEN_WIDTH.value, GUIConstants.SCREEN_HEIGHT.value))
        self.__gui_board = GUIBoard(self.__main_window, (0, 0), GUIConstants.BOARD_DIMENSION.value, GUIConstants.CELL_COLOR.value)
        self.__human_symbol = human_symbol  # the game symbol of the human player
        self.__computer_symbol = computer_symbol  # the game symbol of the computer player

    def __find_board_position(self, window_position):
        """
        Being given a screen position, finds the corresponding cell coordinates in the game board
        :param window_position: a screen position
        :return: the corresponding cell coordinates in the game board
        """
        x, y = window_position[0], window_position[1]
        if x > GUIConstants.BOARD_DIMENSION.value or y > GUIConstants.BOARD_DIMENSION.value:  # the position is not on the board
            return None

        CELL_DIMENSION = GUIConstants.BOARD_DIMENSION.value // self.__gui_board.side
        return Point(x // CELL_DIMENSION, y // CELL_DIMENSION)

    def __human_turn(self, position):
        """
        Attempts to make a human move
        """
        try:
            return self.__game.human_move(self.__human_symbol, self.__find_board_position(position))
        except (CoordinatesError, UserInputError) as inputError:
            return None

    def __computer_turn(self):
        """
        Attempts to make a computer move
        """
        return self.__game.computer_move(self.__computer_symbol)

    def __display_winner(self, winner):
        """
        Display winning message, depending on the winner of the game
        """
        # pygame.time.wait(GUIConstants.END_GAME_TIME_WAIT.value // 2)
        font = pygame.font.Font('freesansbold.ttf', GUIConstants.WINNER_FONT_DIM.value)
        text = font.render('{} won the game.'.format(winner), True, GUIConstants.TEXT_COLOR.value)
        text_rectangle = text.get_rect(center=(GUIConstants.SCREEN_WIDTH.value / 2, 75))
        self.__main_window.fill(GUIConstants.BACKGROUND_COLOR.value)
        self.__gui_board.draw()
        self.__main_window.blit(text, text_rectangle)
        pygame.display.update()
        pygame.time.wait(GUIConstants.END_GAME_TIME_WAIT.value)

    def __handle_mousebuttonup_event(self, position):
        """
        Handles the MOUSEBUTTONUP event
        """
        game_over = self.__human_turn(position)
        if game_over is None:
            return False
        elif game_over:
            self.__gui_board.update_board(self.__game.board)
            self.__main_window.fill(GUIConstants.BACKGROUND_COLOR.value)
            self.__gui_board.draw()
            pygame.display.flip()  # flip everything to the display
            self.__display_winner('Human')
            return True
        game_over = self.__computer_turn()
        if game_over:
            self.__gui_board.update_board(self.__game.board)
            self.__main_window.fill(GUIConstants.BACKGROUND_COLOR.value)
            self.__gui_board.draw()
            # pygame.display.flip()  # flip everything to the display
            self.__display_winner('Computer')
            return True
        return False

    def run(self):
        """
        Runs the UI
        """
        try:
            running = True  # variable to keep the main loop running
            while running:  # the main loop
                for event in pygame.event.get():  # check for every event in the queue
                    running = event.type != QUIT and (event.type != KEYDOWN or event.key != K_ESCAPE)
                    if event.type == pygame.MOUSEBUTTONUP:
                        position = pygame.mouse.get_pos()
                        if self.__handle_mousebuttonup_event(position):
                            running = False
                        self.__gui_board.update_board(self.__game.board)
                self.__main_window.fill(GUIConstants.BACKGROUND_COLOR.value)
                self.__gui_board.draw()
                pygame.display.flip()  # flip everything to the display
        except (UserInputError, CoordinatesError, ServiceGameError) as error:
            pass
