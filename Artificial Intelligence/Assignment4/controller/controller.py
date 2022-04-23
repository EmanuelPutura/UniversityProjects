from queue import PriorityQueue
from random import randint

from domain.ant import Ant
from domain.cell_numeric_representation import CellNumericRepresentation
from utils.utils import VARIATIONS, DRONE_START


class Controller:
    def __init__(self, repository):
        self.__repository = repository
        self.__populationSize = None
        self.__individualSize = None

    def generateRandomMap(self):
        self.__repository.map.randomMap()

    def saveMap(self, filePath):
        self.__repository.saveMap(filePath)

    def loadMap(self, filePath):
        self.__repository.loadMap(filePath)

    def getMap(self):
        return self.__repository.map

    def setSensors(self, sensors):
        self.__repository.map.sensors = sensors

    def __manhattanDistance(self, x1, y1, x2, y2):
        return abs(x2 - x1) + abs(y2 - y1)

    """
        Determine for each sensor position the number of squares that can be discovered for a certain energy value
    """
    def determineMaxDiscoveredCells(self, sensorPosition, energyLevel):
        discoveredCells = 0
        for variation in VARIATIONS:
            currentX = sensorPosition[0] + variation[0]
            currentY = sensorPosition[1] + variation[1]
            currentDiscoveredCells = 0

            while currentDiscoveredCells <= energyLevel and self.__repository.map.isValidCell(currentX, currentY):
                currentDiscoveredCells += 1
                currentX += variation[0]
                currentY += variation[1]

            discoveredCells += currentDiscoveredCells

        return discoveredCells

    """
        Returns the minimum distance path between two cells on the map, using the A Start Algorithm
    """
    def minimumDistanceBetween(self, initialX, initialY, finalX, finalY):
        distance = {}  # a map that associates, to each accessible vertex, the cost of the minimum cost walk from s to it
        previous = {}  # a map that maps each accessible vertex to its predecessor on a path from s to it
        pQueue = PriorityQueue()

        pQueue.put((self.__manhattanDistance(initialX, initialY, finalX, finalY), (initialX, initialY)))
        distance[(initialX, initialY)] = 0
        found = False

        while not pQueue.empty() and not found:
            (_, current) = pQueue.get()
            for variation in VARIATIONS:
                neighbour = (current[0] + variation[0], current[1] + variation[1])
                if neighbour[0] < 0 or neighbour[0] > 19 or neighbour[1] < 0 or neighbour[1] > 19 or \
                        self.__repository.map.surface[neighbour[0]][neighbour[1]] == 1:
                    continue

                if neighbour not in distance.keys() or distance[current] + 1 < distance[neighbour]:
                    distance[neighbour] = distance[current] + 1
                    pQueue.put(
                        (distance[neighbour] + self.__manhattanDistance(neighbour[0], neighbour[1], finalX, finalY),
                         neighbour))
                    previous[neighbour] = current
            if current == (finalX, finalY):
                found = True

        if not found:
            return None

        current = distance[(finalX, finalY)]
        result = [None] * current
        result[current - 1] = previous[(finalX, finalY)]
        current -= 1

        while current > 0:
            result[current - 1] = previous[result[current]]
            current -= 1

        return result

    def __updatePheromoneTrace(self, ants, pheromoneEvaporationConefficient, trace):
        antAddedPheromone = [1.0 / ants[i].fitness for i in range(len(ants))]

        # pheromone evaporation
        for i in range(CellNumericRepresentation.NUMERIC_REPRESENTATION_SUPREMUM + 1):
            for j in range(CellNumericRepresentation.NUMERIC_REPRESENTATION_SUPREMUM + 1):
                trace[i][j] *= (1 - pheromoneEvaporationConefficient)

        # update pheromone trace
        for i in range(len(ants)):
            for j in range(len(ants[i].sensorsPath) - 1):
                sensor1 = ants[i].sensorsPath[j]
                sensor1NumericRepresentation = CellNumericRepresentation.numericRepresentation(sensor1.x, sensor1.y)
                sensor2 = ants[i].sensorsPath[j + 1]
                sensor2NumericRepresentation = CellNumericRepresentation.numericRepresentation(sensor2.x, sensor2.y)

                trace[sensor1NumericRepresentation][sensor2NumericRepresentation] += antAddedPheromone[i]

    def antNextSensor(self, ant, trace, bestChoiceProbability, alpha, beta):
        pass

    def antsEpoch(self, trace, antsNumber, alpha, beta, bestChoiceProbability, pheromoneEvaporationConefficient):
        sensors = self.__repository.map.sensors
        ants = []

        # build the ants with the first visited sensor randomly chosen
        for _ in range(antsNumber):
            currentSensor = sensors[randint(0, len(sensors) - 1)]
            ants.append(Ant(currentSensor, self.minimumDistanceBetween(DRONE_START[0], DRONE_START[1], currentSensor.x, currentSensor.y)))

        # the length of an ant solution is equal to the number of sensors
        for _ in range(len(sensors)):
            for ant in ants:
                self.antNextSensor(ant, trace, bestChoiceProbability, alpha, beta)

        # update the pheromone trace
        self.__updatePheromoneTrace(ants, pheromoneEvaporationConefficient, trace)

        # return the best ant sensors path
        solutions = [[ants[i].fitness(), i] for i in range(len(ants))]
        bestSolution = max(solutions)
        return ants[bestSolution[1]].sensorsPath

    def solve(self):
        pass
