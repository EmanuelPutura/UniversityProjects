import numpy as np
import pygame

from Utils.constants import Constants


class DetectedMap:
    def __init__(self):
        self.__n = Constants.BOARD_DIM
        self.__m = Constants.BOARD_DIM
        self.surface = np.zeros((self.__n, self.__m))
        for i in range(self.__n):
            for j in range(self.__m):
                self.surface[i][j] = -1

    def markDetectedWalls(self, e, x, y):
        # mark on this map the walls that you detect
        walls = e.readUDMSensors(x, y)
        i = x - 1
        if walls[Constants.LEFT] > 0:
            while (i >= 0) and (i >= x - walls[Constants.LEFT]):
                self.surface[i][y] = 0
                i = i - 1
        if i >= 0:
            self.surface[i][y] = 1

        i = x + 1
        if walls[Constants.RIGHT] > 0:
            while (i < self.__n) and (i <= x + walls[Constants.RIGHT]):
                self.surface[i][y] = 0
                i = i + 1
        if i < self.__n:
            self.surface[i][y] = 1

        j = y + 1
        if walls[Constants.DOWN] > 0:
            while (j < self.__m) and (j <= y + walls[Constants.DOWN]):
                self.surface[x][j] = 0
                j = j + 1
        if j < self.__m:
            self.surface[x][j] = 1

        j = y - 1
        if walls[Constants.UP] > 0:
            while (j >= 0) and (j >= y - walls[Constants.UP]):
                self.surface[x][j] = 0
                j = j - 1
        if j >= 0:
            self.surface[x][j] = 1

        return None

    def image(self, x, y):
        imagine = pygame.Surface((Constants.BOARD_DIM * Constants.CELL_SIZE, Constants.BOARD_DIM * Constants.CELL_SIZE))
        brick = pygame.Surface((Constants.CELL_SIZE, Constants.CELL_SIZE))
        empty = pygame.Surface((Constants.CELL_SIZE, Constants.CELL_SIZE))
        empty.fill(Constants.WHITE)
        brick.fill(Constants.BLACK)
        imagine.fill(Constants.GRAYBLUE)

        for i in range(self.__n):
            for j in range(self.__m):
                if self.surface[i][j] == 1:
                    imagine.blit(brick, (j * Constants.CELL_SIZE, i * Constants.CELL_SIZE))
                elif self.surface[i][j] == 0:
                    imagine.blit(empty, (j * Constants.CELL_SIZE, i * Constants.CELL_SIZE))

        drona = pygame.image.load("Resources/Images/drona.png")
        imagine.blit(drona, (y * Constants.CELL_SIZE, x * Constants.CELL_SIZE))
        return imagine
