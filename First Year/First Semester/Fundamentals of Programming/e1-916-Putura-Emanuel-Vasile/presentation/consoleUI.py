from business.game_service import ServiceError
from colors.color import Color


class UserInputError(Exception):
    pass


class ConsoleUI:
    def __init__(self, game_service):
        self.__game_service = game_service
        self.__commands = {'move': self.__move_snake, 'up': self.__change_direction_up, 'down': self.__change_direction_down,
                           'right': self.__change_direction_right, 'left': self.__change_direction_left}

    def __move_snake(self, parameter=1):
        parameter = int(parameter)
        game_state = self.__game_service.move(parameter)
        map_direction = {0: 'up', 1: 'down', 2: 'right', 3: 'left'}
        direction = map_direction[self.__game_service.snake_direction.value]
        if game_state:
            print(Color.FAIL + 'Game over!' + Color.ENDC)
            self.__running = False
            return
        print(self.__game_service.board)
        print(Color.BOLD + 'Current snake direction: {}'.format(direction) + Color.ENDC)

    def __change_direction_up(self):
        if self.__game_service.change_direction(0):
            print(Color.FAIL + 'Game over - snake hits the top wall!' + Color.ENDC)
            self.__running = False
            return
        print(self.__game_service.board)
        print(Color.BOLD + 'Current snake direction: up' + Color.ENDC)

    def __change_direction_down(self):
        if self.__game_service.change_direction(1):
            print(Color.FAIL + 'Game over - snake hits the down wall!' + Color.ENDC)
            self.__running = False
            return
        print(self.__game_service.board)
        print(Color.BOLD + 'Current snake direction: down' + Color.ENDC)

    def __change_direction_right(self):
        if self.__game_service.change_direction(2):
            print(Color.FAIL + 'Game over - snake hits the right wall!' + Color.ENDC)
            self.__running = False
            return
        print(self.__game_service.board)
        print(Color.BOLD + 'Current snake direction: right' + Color.ENDC)

    def __change_direction_left(self):
        if self.__game_service.change_direction(3):
            print(Color.FAIL + 'Game over - snake hits the left wall!' + Color.ENDC)
            self.__running = False
            return
        print(self.__game_service.board)
        print(Color.BOLD + 'Current snake direction: left' + Color.ENDC)

    def __print_menu(self):
        print(Color.OKGREEN + Color.BOLD + '\n' + '-' * 30 + ' Snake Game ' + '-' * 30)
        print(' move [n] - moves the snake n squares, in the direction of the snake')
        print(' up/down/right/left - changes the direction the snake is facing')
        print(' exit - exit the application')
        print('-' * 72 + '\n' + Color.ENDC)

    def __parse_command(self, command):
        command = command.split(' ')
        if len(command) not in [1, 2]:
            raise UserInputError('Invalid command.\n')
        if len(command) == 1:
            return command[0], ''
        return command[0], command[1]

    def run(self):
        self.__running = True
        self.__game_service.board.initialize_board()
        print(self.__game_service.board)
        print(Color.BOLD + 'Current snake direction: up' + Color.ENDC)

        while self.__running:
            try:
                self.__print_menu()
                command = input('command > ').strip()
                if command == 'exit':
                    break
                command, parameter = self.__parse_command(command)
                if command in self.__commands and parameter != '':
                    self.__commands[command](parameter)
                elif command in self.__commands:
                    self.__commands[command]()
                else:
                    print(Color.FAIL + "'{}' is not a valid command.".format(command) + Color.ENDC)
                    print(self.__game_service.board)
            except ServiceError as se:
                print(Color.FAIL + str(se) + Color.ENDC)
            except UserInputError as uie:
                print(Color.FAIL + str(uie) + Color.ENDC)
            except Exception as exception:
                print(Color.FAIL + 'Unexpected exception occurred: ' + str(exception) + Color.ENDC)
