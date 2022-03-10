import pickle
from random import random, randint

import numpy as np
import pygame

from Utils.constants import Constants


class Environment:
    def __init__(self):
        self.__n = Constants.BOARD_DIM
        self.__m = Constants.BOARD_DIM
        self.__surface = np.zeros((self.__n, self.__m))

    def loadMapFromTxt(self, file_name):
        with open(file_name, "r") as file:
            i = 0
            for line in file:
                j = 0
                for value in line.split(' '):
                    self.__surface[i][j] = value
                    j += 1
                i += 1

    def randomMap(self, fill=Constants.FILL_FACTOR):
        for i in range(self.__n):
            for j in range(self.__m):
                if random() <= fill:
                    self.__surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.__n):
            for j in range(self.__m):
                string = string + str(int(self.__surface[i][j]))
            string = string + "\n"
        return string

    def readUDMSensors(self, x, y):
        readings = [0, 0, 0, 0]
        # UP
        xf = x - 1
        while (xf >= 0) and (self.__surface[xf][y] == 0):
            xf = xf - 1
            readings[Constants.LEFT] = readings[Constants.LEFT] + 1
        # DOWN
        xf = x + 1
        while (xf < self.__n) and (self.__surface[xf][y] == 0):
            xf = xf + 1
            readings[Constants.RIGHT] = readings[Constants.RIGHT] + 1
        # LEFT
        yf = y + 1
        while (yf < self.__m) and (self.__surface[x][yf] == 0):
            yf = yf + 1
            readings[Constants.DOWN] = readings[Constants.DOWN] + 1
        # RIGHT
        yf = y - 1
        while (yf >= 0) and (self.__surface[x][yf] == 0):
            yf = yf - 1
            readings[Constants.UP] = readings[Constants.UP] + 1

        return readings

    def saveEnvironment(self, num_file):
        with open(num_file, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def loadEnvironment(self, num_file):
        with open(num_file, "rb") as f:
            dummy = pickle.load(f)
            self.__n = dummy.__n
            self.__m = dummy.__m
            self.__surface = dummy.__surface
            f.close()

    def image(self):
        imagine = pygame.Surface((Constants.BOARD_DIM * Constants.CELL_SIZE, Constants.BOARD_DIM * Constants.CELL_SIZE))
        brick = pygame.Surface((Constants.CELL_SIZE, Constants.CELL_SIZE))
        brick.fill(Constants.BLUE)
        imagine.fill(Constants.WHITE)
        for i in range(self.__n):
            for j in range(self.__m):
                if self.__surface[i][j] == 1:
                    imagine.blit(brick, (j * Constants.CELL_SIZE, i * Constants.CELL_SIZE))

        return imagine

    def randomEmptyPosition(self):
        x = randint(0, Constants.BOARD_DIM - 1)
        y = randint(0, Constants.BOARD_DIM - 1)

        while self.__surface[x][y] != 0:
            x = randint(0, Constants.BOARD_DIM - 1)
            y = randint(0, Constants.BOARD_DIM - 1)
        return x, y
