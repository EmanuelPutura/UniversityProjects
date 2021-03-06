from random import random
import numpy as np
from utils.utils import FILL_FACTOR, START_POSITION, MAP_LENGTH, VARIATIONS


class Map:
    def __init__(self, n=20, m=20):
        self.__n = n
        self.__m = m
        self.__surface = np.zeros((self.__n, self.__m))

    @property
    def rows(self):
        return self.__n

    @property
    def columns(self):
        return self.__m

    @property
    def surface(self):
        return self.__surface

    def setSurfaceCell(self, x, y, value):
        self.__surface[x][y] = value

    def randomMap(self, fill=FILL_FACTOR):
        self.__surface = np.zeros((self.__n, self.__m))

        for i in range(self.__n):
            for j in range(self.__m):
                if random() <= fill:
                    self.__surface[i][j] = 1

        # the start position is never occupied
        self.__surface[START_POSITION[0]][START_POSITION[1]] = 0

    def isValidCell(self, x, y):
        return 0 <= x < MAP_LENGTH and 0 <= y < MAP_LENGTH and self.__surface[x][y] != 1

    def markSensorObservedCells(self, startX, startY):
        markedCells = 0
        for variation in VARIATIONS:
            x = startX
            y = startY

            while self.isValidCell(x, y):
                if self.__surface[x][y] != 2:
                    markedCells += 1

                self.__surface[x][y] = 2
                x += variation[0]
                y += variation[1]
        return markedCells

    def __str__(self):
        string = ""
        for i in range(self.__n):
            for j in range(self.__m):
                string = string + str(int(self.__surface[i][j]))
            string = string + "\n"
        return string

    def __deepcopy__(self):
        newMap = Map(self.__n, self.__m)
        for i in range(self.__n):
            for j in range(self.__m):
                newMap.setSurfaceCell(i, j, self.__surface[i][j])
        return newMap
