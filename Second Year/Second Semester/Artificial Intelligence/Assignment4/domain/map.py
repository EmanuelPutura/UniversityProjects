from random import random
import numpy as np

from domain.sensor import Sensor
from utils.utils import FILL_FACTOR, MAP_LENGTH, DRONE_START, SENSORS


class Map:
    def __init__(self, sensors=SENSORS, n=20, m=20):
        self.__n = n
        self.__m = m
        self.__surface = np.zeros((self.__n, self.__m))
        self.__sensors = [Sensor(sensor[0], sensor[1]) for sensor in sensors]

    @property
    def rows(self):
        return self.__n

    @property
    def columns(self):
        return self.__m

    @property
    def surface(self):
        return self.__surface

    @property
    def sensors(self):
        return self.__sensors

    @sensors.setter
    def sensors(self, other):
        self.__sensors = [Sensor(sensor[0], sensor[1]) for sensor in other]

        # the sensors positions should never be occupied
        for sensor in other:
            self.__surface[sensor[0]][sensor[1]] = 0

    @property
    def sensorsNumber(self):
        return len(self.__sensors)

    def setSurfaceCell(self, x, y, value):
        self.__surface[x][y] = value

    def randomMap(self, fill=FILL_FACTOR):
        self.__surface = np.zeros((self.__n, self.__m))

        for i in range(self.__n):
            for j in range(self.__m):
                if random() <= fill:
                    self.__surface[i][j] = 1

        # the start position and the sensor positions are never occupied
        self.__surface[DRONE_START[0]][DRONE_START[1]] = 0
        for sensor in self.__sensors:
            self.__surface[sensor.x][sensor.y] = 0

    def isValidCell(self, x, y):
        return 0 <= x < MAP_LENGTH and 0 <= y < MAP_LENGTH and self.__surface[x][y] != 1

    def __str__(self):
        string = ""
        for i in range(self.__n):
            for j in range(self.__m):
                string = string + str(int(self.__surface[i][j]))
            string = string + "\n"
        return string

    def __deepcopy__(self):
        newMap = Map(self.__sensors, self.__n, self.__m)
        for i in range(self.__n):
            for j in range(self.__m):
                newMap.setSurfaceCell(i, j, self.__surface[i][j])
        return newMap
