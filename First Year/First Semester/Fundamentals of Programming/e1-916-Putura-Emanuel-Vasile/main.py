from jproperties import Properties

from business.game_service import GameService
from game_board.board import Board
from presentation.consoleUI import ConsoleUI


class ProgramSettings:
    """
    Program settings of the class. Manages the initial program settings, i.e., the dimension of the
    game board and the number of apples to be placed on the board
    """
    def __init__(self, file_path):
        properties = Properties()
        with open(file_path, 'rb') as configuration_file:
            properties.load(configuration_file)
        try:
            self.__dimension = int(properties['dimension'].data)
            self.__apples_count = int(properties['apples_count'].data)
        except Exception as exception:
            print("Unexpected exception occurred: '{}'.\n".format(exception))
            exit(0)

    @property
    def dimension(self):
        return self.__dimension

    @property
    def apples_count(self):
        return self.__apples_count


if __name__ == "__main__":
    program_settings = ProgramSettings('settings.properties')
    game_board = Board(program_settings.apples_count, program_settings.dimension)
    game_service = GameService(game_board)
    consoleUI = ConsoleUI(game_service)
    consoleUI.run()
