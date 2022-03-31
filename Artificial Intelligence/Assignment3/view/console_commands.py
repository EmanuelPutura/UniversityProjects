import timeit

from utils.utils import START_POSITION
from view.gui import movingDrone


class ConsoleCommands:
    def __init__(self, controller):
        self.__controller = controller

    def randomMapCommand(self):
        self.__controller.generateRandomMap()

    def loadMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.loadMap(filePath)

    def saveMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.saveMap(filePath)

    def displayMapCommand(self):
        print("map.display!")

    def eaSetupCommand(self):
        print("ea.setup!")

    def eaRunCommand(self):
        startTime = timeit.default_timer()
        solutionPath = self.__controller.solver(50, 10)
        endTime = timeit.default_timer()

        print("Time: {}".format(str(endTime - startTime)))
        movingDrone(self.__controller.getMap(), solutionPath)

    def eaStatisticsCommand(self):
        print("ea.statistics!")

    def eaDroneCommand(self):
        print("ea.drone!")
