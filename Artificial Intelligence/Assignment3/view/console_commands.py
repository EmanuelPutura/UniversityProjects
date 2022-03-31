import timeit

from utils.utils import START_POSITION
from view.gui import movingDrone


class ConsoleCommands:
    def __init__(self, controller):
        self.__controller = controller

    def randomMapCommand(self):
        self.__controller.getMap().randomMap()

    def loadMapCommand(self):
        print("map.load!")

    def saveMapCommand(self):
        print("map.save!")

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
