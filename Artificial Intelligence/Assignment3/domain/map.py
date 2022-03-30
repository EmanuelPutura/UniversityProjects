from random import random

import numpy as np

from utils import VARIATIONS, MAP_LENGTH, FILL_FACTOR, START_POSITION


class Map:
    def __init__(self, n=20, m=20):
        self.__n = n
        self.__m = m
        self.__surface = np.zeros((self.__n, self.__m))

    def setSurfaceCell(self, x, y, value):
        self.__surface[x][y] = value

    def randomMap(self, fill=FILL_FACTOR):
        for i in range(self.__n):
            for j in range(self.__m):
                if random() <= fill:
                    self.__surface[i][j] = 1

        # the start position is never occupied
        self.__surface[START_POSITION[0]][START_POSITION[1]] = 0

    def __isValidCell(self, x, y):
        return 0 <= x < MAP_LENGTH and 0 <= y < MAP_LENGTH and self.__surface[x][y] != 1

    def markSensorObservedCells(self, startX, startY):
        markedCells = 0
        for variation in VARIATIONS:
            x = startX
            y = startY

            while self.__isValidCell(x, y):
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
