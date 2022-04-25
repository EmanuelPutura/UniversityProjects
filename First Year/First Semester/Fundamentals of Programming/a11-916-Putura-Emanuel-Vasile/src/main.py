"""
    Obstruction Game (~ 01.2021)
    - Emanuel-Vasile Putura

    You can pick the game settings (i.e., the UI, the AI strategy, the human/computer player symbol) from the settings.properties file.
    Default game state:
        ui = gui
        strategy = beginner
        human_symbol = X
        computer_symbol = O

    Also note that for the second player symbol the letter 'O' is used instead of '0', because of displaying considerations.

"""
from jproperties import Properties
from presentation.GUI.gui import GUI
from presentation.consoleUI.consoleUI import ConsoleUI
from src.board.board import Board
from services.game_service import GameService
from strategy.beginner_strategy import BeginnerStrategy
from strategy.minimax_strategy import MinimaxStrategy
from strategy.random_strategy import RandomStrategy


class ProgramSettings:
    """
    ProgramSettings class manages the game start settings (i.e., the UI, the AI strategy, the human/computer player symbol),
    defined in the settings.properties file
    """
    def __init__(self, file_path):
        properties = Properties()
        with open(file_path, 'rb') as configuration_file:
            properties.load(configuration_file)
        try:
            self.__ui = self.__get_ui(properties['ui'].data)
            self.__strategy = self.__get_strategy(properties['strategy'].data)
            self.__human_symbol = properties['human_symbol'].data
            self.__computer_symbol = properties['computer_symbol'].data
        except KeyError as keyError:
            print(keyError, '\n')
        except Exception as exception:
            print("Unexpected exception occurred: '{}'.\n".format(exception))
            exit(0)

    def __get_ui(self, ui):
        """
        Gets the class corresponding to the ui picked from settings.properties file
        """
        ui_dict = {'console': ConsoleUI, 'gui': GUI}  # dictionary mapping the possible ui options with the corresponding ui class
        return ui_dict[ui]

    def __get_strategy(self, strategy):
        """
        Gets the class corresponding to the strategy picked from settings.properties file
        """
        # dictionary mapping the possible strategy options with the corresponding strategy class
        strategy_dict = {'random': RandomStrategy, 'beginner': BeginnerStrategy, 'minimax': MinimaxStrategy}
        return strategy_dict[strategy]

    @property
    def ui(self):
        return self.__ui

    @property
    def strategy(self):
        return self.__strategy

    @property
    def human(self):
        return self.__human_symbol

    @property
    def computer(self):
        return self.__computer_symbol


if __name__ == "__main__":
    SETTINGS_FILE_PATH = '../settings.properties'
    settings = ProgramSettings(SETTINGS_FILE_PATH)
    board = Board()
    strategy = settings.strategy()
    game = GameService(board, strategy)
    ui = settings.ui(game, settings.human, settings.computer)
    ui.run()
