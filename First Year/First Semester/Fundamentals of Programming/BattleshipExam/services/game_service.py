from random import randint

from game_board.board import Board
from game_board.cell import CellState


class ServiceError(Exception):
    pass


class GameService:
    """
        The game service class
    """
    def __init__(self, board):
        self.__human_board = board
        self.__targeting_board = Board(board.rows, board.columns)
        self.__human_ships = []
        self.__computer_ships = [[], []]  # positions of the computer's ships

    @property
    def human_board(self):
        return self.__human_board

    @property
    def targeting_board(self):
        return self.__targeting_board

    @property
    def human_ships(self):
        return self.__human_ships

    @property
    def computer_ships(self):
        return self.__computer_ships

    def delete_past_ships(self, points):
        """
        Delete past occupied cells in case ships are moved from their initial place
        :param points: the past ship's coordinates
        """
        for point in points:
            self.__human_board[point[1]][point[0]].state = CellState.FREE

    def place_ship(self, points, human_player=True):
        """
        Places a ship at given positions
        :param points: the position points of the ship (a list of lists of 2 elements, x and y of the current point)
        :param human_player: True if human's ships need to be placed, False else
        :return:
        """
        state_map = {True: CellState.PLAYER_SHIP, False: CellState.COMPUTER_SHIP}

        for point in points:
            if self.__human_board[point[1]][point[0]].state != CellState.FREE:
                raise ServiceError('Cell already occupied.\n')
            self.__human_board[point[1]][point[0]].state = state_map[human_player]

        if len(self.__human_ships) == 2:
            self.delete_past_ships(self.__human_ships[0])
            self.__human_ships[0] = points
        elif len(self.__human_ships) < 2:
            self.__human_ships.append(points)

    def player_attack(self, square):
        return_value = None
        square[0], square[1] = square[1], square[0]
        for ship in self.__computer_ships:
            if square in ship:
                self.__targeting_board[square[0]][square[1]].state = CellState.HIT
                return_value = 2
                break
            self.__targeting_board[square[0]][square[1]].state = CellState.MISSED
            return_value = 0

        index = 0
        not_done = [0, 0]
        for ship in self.__computer_ships:
            not_done[index] = False
            for position in ship:
                if self.__targeting_board[position[0]][position[1]].state != CellState.HIT:
                    not_done[index] = True
                    break
            index += 1
        if not not_done[0] and not not_done[1]:
            return 1  # player win
        return return_value

    def get_computer_ships(self):
        computer_board = Board()
        for ship in self.__computer_ships:
            for point in ship:
                computer_board[point[0]][point[1]].state = CellState.COMPUTER_SHIP
        return computer_board

    def computer_attack(self):
        x_attack = randint(0, 5)
        y_attack = randint(0, 5)
        if self.__human_board[x_attack][y_attack].state == CellState.PLAYER_SHIP:
            self.__human_board[x_attack][y_attack].state = CellState.HIT

            index = 0
            not_done = [0, 0]
            for ship in self.__human_ships:
                not_done[index] = False
                for position in ship:
                    if self.__human_board[position[0]][position[1]].state != CellState.HIT:
                        not_done[index] = True
                        break
                index += 1
            if not not_done[0] and not not_done[1]:
                return 1  # computer win
            return 2  # computer hit, but no win
        elif self.__human_board[x_attack][y_attack].state == CellState.FREE:
            self.__human_board[x_attack][y_attack].state = CellState.MISSED
        return 0

    def randomly_place_ships(self):
        """
        Randomly places computers's ships on the board
        """
        for i in range(2):
            not_done = True
            while not_done:
                self.__computer_ships[i] = []

                ship_size = randint(1, 4)
                start_x = randint(0, 5)
                start_y = randint(0, 5)
                horizontal = randint(0, 1)

                self.__computer_ships[i].append([start_x, start_y])
                not_done = False
                if horizontal:
                    right = randint(0, 1)
                    for j in range(1, ship_size):
                        if right == 1:
                            if start_y + j not in range(0, 6):
                                not_done = True
                                break
                            self.__computer_ships[i].append([start_x, start_y + j])
                        else:
                            if start_y - j not in range(0, 6):
                                not_done = True
                                break
                            self.__computer_ships[i].append([start_x, start_y - j])
                else:
                    up = randint(0, 1)
                    for j in range(1, ship_size):
                        if up == 1:
                            if start_x + j not in range(0, 6):
                                not_done = True
                                break
                            self.__computer_ships[i].append([start_x + j, start_y])
                        else:
                            if start_x + j not in range(0, 6):
                                not_done = True
                                break
                            self.__computer_ships[i].append([start_x - j, start_y])

                if i == 1:
                    for ship in self.__computer_ships[1]:
                        if ship in self.__computer_ships[0]:
                            not_done = True
