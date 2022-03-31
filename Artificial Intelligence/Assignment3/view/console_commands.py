import timeit

from utils.utils import START_POSITION
from view.gui import movingDrone


class ConsoleCommands:
    def __init__(self, controller):
        self.__solutionPath = []
        self.__controller = controller

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

    def eaSetupCommand(self):
        try:
            self.__populationSize = int(input("Please input the population size: "))
        except Exception as error:
            print("Error: {}".format(str(error)))

        try:
            self.__individualSize = int(input("Please input the maximum number of steps the drone can make: "))
        except Exception as error:
            print("Error: {}".format(str(error)))

    def eaRunCommand(self):
        startTime = timeit.default_timer()
        self.__solutionPath = self.__controller.solver(self.__populationSize, self.__individualSize)
        endTime = timeit.default_timer()

        print("Time: {}".format(str(endTime - startTime)))

    def eaStatisticsCommand(self):
        print("ea.statistics!")

    def eaDroneCommand(self):
        if not self.__solutionPath:
            print("You must first run the evolutionary algorithm!")
            return
        movingDrone(self.__controller.getMap(), self.__solutionPath)
