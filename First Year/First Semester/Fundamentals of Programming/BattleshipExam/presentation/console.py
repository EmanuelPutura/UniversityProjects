from services.game_service import ServiceError


class UserInputError(Exception):
    pass


class ConsoleUI:
    def __init__(self, game_service):
        self.__running_game = False
        self.__game_service = game_service
        self.__commands = {'ship': self.__place_ship, 'start': self.__start_game, 'attack': self.__attack_square,
                          'cheat': self.__activate_cheats}

    def __place_ship(self, position):
        """
        Places ships given as input by user on the board
        :param position: positions of the ships
        :raises: UserInputError if the provided ship position is not valid
        """
        points = []
        index = 0
        positions_map = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5}

        for point in position:
            if index % 2 == 0:
                if point not in positions_map:
                    raise UserInputError('Invalid ship position.\n')
                points.append([])
                point = positions_map[point]
            if index % 2 == 1 and int(point) not in range(6):
                raise UserInputError('Invalid ship position.\n')

            points[index // 2].append(int(point))
            index += 1
        self.__game_service.place_ship(points)
        print(self.__game_service.human_board)

    def __start_game(self):
        """
        Starts the game (after positioning the ships)
        :raises: UserInputError if 2 ships have not been placed yet by the human player
        """
        self.__running_game = True
        if len(self.__game_service.human_ships) != 2:
            raise UserInputError('Two ships need to be placed before the game start.\n')
        self.__game_service.randomly_place_ships()

    def __attack_square(self, square):
        if not self.__running_game:
            raise UserInputError('Game has not started yet.\n')
        if len(square) != 2:
            raise UserInputError('Invalid position.\n')
        positions_map = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5}
        if square[0] not in positions_map:
            raise UserInputError('Invalid position.\n')
        points = [positions_map[square[0]]]
        if int(square[1]) not in range(0, 6):
            raise UserInputError('Invalid position.\n')
        points.append(int(square[1]))

        state = self.__game_service.player_attack(points)
        print('Player Board:')
        print(self.__game_service.human_board)
        print('Targeting board:')
        print(self.__game_service.targeting_board)
        if state == 1:
            print('Player won the game!')
            self.__running_game = False
            return
        elif state == 2:
            print('Player hit!')
        elif state == 0:
            print('Player missed!')
        state = self.__game_service.computer_attack()
        if state == 1:
            print('Computer won the game!')
            self.__running_game = False
            return
        elif state == 2:
            print('Computer hit!')
        elif state == 0:
            print('Computer missed!')

    def __activate_cheats(self):
        if not self.__running_game:
            raise UserInputError('Game has not started yet.\n')
        print('Cheats activated. Computer ships are:')
        print(self.__game_service.get_computer_ships())

    def __print_menu(self):
        print('-' * 20 + ' Battleship Application ' + '-' * 20)
        print(' ship <C1L1C2L2C3L3> - place a ship on the board')
        print(' start - start the game')
        print(' attack <C1L1> - attack a board square')
        print(' cheat - activate cheats')
        print(' exit - exit the application')
        print('-' * 64)

    def __parse_command(self, command):
        """
        Parses a given user command
        :param command: a user command
        :return: the command and its parameters
        """
        command = command.split(' ')
        return command

    def run(self):
        """
        Runs the application console UI
        """
        while True:
            try:
                self.__print_menu()
                command = input('command > ').strip()
                if command == 'exit':
                    return
                command = self.__parse_command(command)
                if command[0] in self.__commands:
                    if len(command) == 1:
                        self.__commands[command[0]]()
                    else:
                        self.__commands[command[0]](command[1])
                else:
                    print('Invalid command.\n')
            except UserInputError as uie:
                print(uie)
            except ServiceError as se:
                print(se)
            except Exception as ex:
                print(ex)
