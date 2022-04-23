from queue import PriorityQueue

from utils.utils import VARIATIONS


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

    def __manhattanDistance(self, x1, y1, x2, y2):
        return abs(x2 - x1) + abs(y2 - y1)

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

    def solve(self):
        pass
