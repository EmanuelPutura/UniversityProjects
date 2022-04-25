from domain.point import Point
from services.game_service import CoordinatesError, ServiceGameError


class UserInputError(Exception):
    """
    Custom exception class representing an user input error
    """
    def __init__(self, message):
        self._message = message

    def __str__(self):
        return self._message


class ConsoleUI:
    """
    ConsoleUI class implements the console UI. This UI can be chosen from the settings.properties file of the application
    """
    def __init__(self, game, human_symbol, computer_symbol):
        self.__game = game  # the game service
        self.__human_symbol = human_symbol  # the human player symbol used during the game
        self.__computer_symbol = computer_symbol  # the computer player symbol used during the game

    def __pick_symbol(self):
        """
        Note that this method is not currently used in the application anymore, as the player symbols are now selected from the
        settings.properties file. The function was kept in case of changing the current implemention

        Establishes the player symbols the human and the computer will play with
        :return: a tuple with two elements, the first one being the human symbol and the second one the
        computer symbol
        :raises: UserInputError if the chosen symbol is not an accepted one
        """
        found_symbol = False
        while not found_symbol:
            found_symbol = True
            symbol = input("Pick your player: 'X' or 'O' > ")
            options = ['X', 'O']
            if symbol.upper() not in options:
                print("'{}' is not a valid symbol. Try again.\n".format(symbol))
                found_symbol = False
            else:
                return symbol.upper(), options[options.index(symbol.upper()) - 1]

    def __human_turn(self):
        """
        Attempts to perform a human move
        """
        move_completed = False
        while not move_completed:
            try:
                move_completed = True
                print("Human's turn: ")
                coordinates = self.__read_human_move()
                game_over = self.__game.human_move(self.__human_symbol, coordinates)
                print('Human move successfully performed.\n')
                return game_over
            except (CoordinatesError, UserInputError) as inputError:
                print(inputError)
                move_completed = False

    def __computer_turn(self):
        """
        Attempts to perform a computer move
        """
        print("Computer's turn: ")
        print('Computer move successfully performed.\n')
        return self.__game.computer_move(self.__computer_symbol)

    def __read_human_move(self):
        """
        Gets the coordinates of a human move
        :return: a point having the (x, y) coordinates of a human move
        :raises: UserInputError if the given coordinates are not positive integers
        """
        x_coordinate = input('Please input the x coordinate of your move > ')
        y_coordinate = input('Please input the y coordinate of your move > ')
        if not x_coordinate.isdigit() or not y_coordinate.isdigit():
            raise UserInputError('({}, {}) is not a valid pointx.\n'.format(x_coordinate, y_coordinate))
        return Point(int(x_coordinate) - 1, int(y_coordinate) - 1)

    def __draw_board(self):
        """
        Draws the game board
        """
        print(self.__game.board)

    def run(self):
        """
        Runs the UI
        """
        try:
            # self.__human_symbol, self.__computer_symbol = self.__pick_symbol()
            symbol_turn = {self.__human_symbol: self.__human_turn, self.__computer_symbol: self.__computer_turn}
            game_over = False

            while not game_over:
                self.__draw_board()
                game_over = symbol_turn['X']()
                self.__draw_board()
                if game_over:
                    print('Player X won the game.\n')
                else:
                    game_over = symbol_turn['O']()
                    if game_over:
                        print('Player O won the game.\n')
            self.__draw_board()
        except (UserInputError, CoordinatesError, ServiceGameError) as error:
            print(error, '\n')
        except Exception as exception:
            print("Unexpected exception occurred: '{}'.\n".format(exception))
