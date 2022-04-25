from random import randint

from texttable import Texttable

from game_board.cell import Cell, CellState


class Board:
    """
        The game board
    """
    def __init__(self, apple_count=0, dimension=7):
        self.__apple_count = apple_count
        self.__dimension = dimension
        self.__board = self.__create_board()

    @property
    def dimension(self):
        return self.__dimension

    @property
    def apple_count(self):
        return self.__apple_count

    def __create_board(self):
        """
        Creates the game board (basically a matrix)
        :return: a matrix representing the game board
        """
        return [[Cell() for j in range(self.__dimension)] for i in range(self.__dimension)]

    def initialize_board(self, apple_count=0):
        """
        Initializez the board with the snake and the apples
        :param apple_count: the number of apples to be placed on the board
        """
        dimension = self.__dimension
        middle = dimension // 2

        self.__board[middle][middle].place_snake_body()
        self.__board[middle + 1][middle].place_snake_body()
        self.__board[middle - 1][middle].place_snake_head()
        self.place_random_apples(self.__apple_count)

    def get_put_apples(self):
        """
        Gets the already put apples on the table
        """
        put_apples = []
        for i in range(self.__dimension):
            for j in range(self.__dimension):
                if self.__board[i][j].state == CellState.APPLE:
                    put_apples.append([i, j])
        return put_apples

    def place_random_apples(self, apples_no):
        """
        Places some random apples on the table
        """
        put_apples = self.get_put_apples()
        while len(put_apples) < apples_no:
            row = randint(0, self.__dimension - 1)
            column = randint(0, self.__dimension - 1)

            if self.__board[row][column].state != CellState.FREE:
                continue

            must_continue = False
            for apple in put_apples:
                if abs(apple[0] - row) <= 1 and abs(apple[1] - column) <= 1:
                    must_continue = True
                    break
            if must_continue:
                continue

            put_apples.append([row, column])
            self.__board[row][column].state = CellState.APPLE

    def __getitem__(self, key):
        return self.__board[key]

    def __str__(self):
        """
        Gets the string representation of the board
        """
        representation = Texttable()

        for row in range(self.__dimension):
            row_data = [self.__board[row][column] for column in range(self.__dimension)]
            representation.add_row(row_data)
        return representation.draw()
