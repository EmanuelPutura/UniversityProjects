import timeit

import matplotlib.pyplot
import numpy

from utils.utils import START_POSITION, RUNNING_TIMES
from view.gui import movingDrone


class ConsoleCommands:
    def __init__(self, controller, randomGenerator):
        self.__solutionPath = []
        self.__controller = controller
        self.__randomGenerator = randomGenerator

        self.__populationSize = 2
        self.__individualSize = 5

    def randomMapCommand(self):
        self.__controller.generateRandomMap()

    def loadMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.loadMap(filePath)

    def saveMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.saveMap(filePath)

    def displayMapCommand(self):
        movingDrone(self.__controller.getMap(), [START_POSITION], 0, False)

    def setDroneStartPositionCommand(self):
        pass

    def setDroneEnergyCommand(self):
        pass

    def setSensorsPositionCommand(self):
        pass

    def runAlgorithmCommand(self):
        pass

    def showDronePathCommand(self):
        pass
