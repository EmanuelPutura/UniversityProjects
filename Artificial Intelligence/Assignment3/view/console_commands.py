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
        runMultipleTimesAndDoStatistics = None
        answer = None
        while answer is None or (answer != "Y" and answer != "N"):
            if answer is not None:
                print("'{}' is not a valid answer!".format(answer))
            answer = input("Want to generate statistics? [Y|N] >> ")

        if answer == "Y":
            runMultipleTimesAndDoStatistics = True
        elif answer == "N":
            runMultipleTimesAndDoStatistics = False

        if runMultipleTimesAndDoStatistics:
            bestFitness = []
            for i in range(RUNNING_TIMES):
                self.__randomGenerator.seed = self.__randomGenerator.randint(0, 100)
                (_, _, solution) = self.__controller.solver(self.__populationSize, self.__individualSize)
                bestFitness.append(solution.fitness)
                print(solution.fitness)

            print("Average best fitness: {}".format(numpy.average(bestFitness)))
            print("Variation of best fitnesses: {}".format(numpy.std(bestFitness)))
        else:
            startTime = timeit.default_timer()
            (self.__solutionPath, averageFitness, _) = self.__controller.solver(self.__populationSize, self.__individualSize)
            endTime = timeit.default_timer()

            print("Time: {}".format(str(endTime - startTime)))

            # plot statistics
            matplotlib.pyplot.plot([i for i in range(len(averageFitness))], averageFitness)
            matplotlib.pyplot.show()

    def eaStatisticsCommand(self):
        print("ea.statistics!")

    def eaDroneCommand(self):
        if not self.__solutionPath:
            print("You must first run the evolutionary algorithm!")
            return
        movingDrone(self.__controller.getMap(), self.__solutionPath)
