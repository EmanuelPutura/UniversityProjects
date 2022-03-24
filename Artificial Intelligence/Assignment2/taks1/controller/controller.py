import math
import random
import timeit
from queue import PriorityQueue
from random import randint

from taks1.domain.drone import Drone
from taks1.domain.map import Map
from taks1.utils.constants import Constants


class Controller:
    def __init__(self):
        self.__map = Map()
        self.__startX, self.__startY = self.__generateRandomPosition()
        self.__drone = Drone(self.__startX, self.__startY)

    def __manhattanDistance(self, x1, y1, x2, y2):
        return abs(x2 - x1) + abs(y2 - y1)

    def __generateRandomPosition(self):
        # we position the drone somewhere in the area
        return randint(0, 19), randint(0, 19)

    def dummysearch(self):
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]

    def __searchAStar(self, mapM, initialX, initialY, finalX, finalY):
        start_time = timeit.default_timer()
        distance = {}  # a map that associates, to each accessible vertex, the cost of the minimum cost walk from s to it
        previous = {}  # a map that maps each accessible vertex to its predecessor on a path from s to it
        pQueue = PriorityQueue()

        pQueue.put((self.__manhattanDistance(initialX, initialY, finalX, finalY), (initialX, initialY)))
        distance[(initialX, initialY)] = 0
        found = False

        while not pQueue.empty() and not found:
            (_, current) = pQueue.get()
            for variation in Constants.VARIATIONS:
                neighbour = (current[0] + variation[0], current[1] + variation[1])
                if neighbour[0] < 0 or neighbour[0] > 19 or neighbour[1] < 0 or neighbour[1] > 19 or \
                        mapM.surface[neighbour[0]][neighbour[1]] == 1:
                    continue

                if neighbour not in distance.keys() or distance[current] + 1 < distance[neighbour]:
                    distance[neighbour] = distance[current] + 1
                    pQueue.put((distance[neighbour] + self.__manhattanDistance(neighbour[0], neighbour[1], finalX, finalY),
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

        end_time = timeit.default_timer()
        print("Simulated Annealing Time: {}".format(end_time - start_time))
        return result

    def __searchGreedy(self, mapM, initialX, initialY, finalX, finalY, printTime=True):
        start_time = timeit.default_timer()
        found = False
        visited = []
        toVisit = PriorityQueue()
        toVisit.put((self.__manhattanDistance(initialX, initialY, finalX, finalY), initialX, initialY))

        while not toVisit.empty() and not found:
            (_, nodeX, nodeY) = toVisit.get()
            visited.append((nodeX, nodeY))
            if (nodeX, nodeY) == (finalX, finalY):
                found = True

            # check neighbours of current node
            for variation in [(0, -1), (1, 0), (0, 1), (-1, 0)]:
                current = (nodeX + variation[0], nodeY + variation[1])
                if current not in visited and 0 <= current[0] <= 19 and 0 <= current[1] <= 19 and \
                        mapM.surface[current[0]][current[1]] != 1:
                    toVisit.put((self.__manhattanDistance(nodeX + variation[0], nodeY + variation[1], finalX, finalY),
                                 nodeX + variation[0], nodeY + variation[1]))

        end_time = timeit.default_timer()
        if printTime:
            print("Simulated Annealing Time: {}".format(end_time - start_time))
        return None if not found else visited

    def __searchSimulatedAnnealing(self, mapM, initialX, initialY, finalX, finalY):
        T = 1
        TMin = 0.0001
        alpha = 0.9

        start_time = timeit.default_timer()

        min_sol = self.__searchGreedy(mapM, initialX, initialY, finalX, finalY, False)
        current_sol = min_sol
        pos = 0

        while T > TMin and pos < len(min_sol):
            for _ in range(10):
                x = min_sol[pos][0]
                y = min_sol[pos][1]

                if len(current_sol) < len(min_sol):
                    min_sol = current_sol

                i = random.randint(0, 3)

                if not (0 <= x + Constants.VARIATIONS[i][0] < 20 and 0 <= y + Constants.VARIATIONS[i][1] < 20 and
                        mapM.surface[x + Constants.VARIATIONS[i][0]][y + Constants.VARIATIONS[i][1]] != 1):
                    continue

                next_sol = min_sol[:pos + 1]
                next_sol.extend(self.__searchGreedy(mapM, x + Constants.VARIATIONS[i][0], y + Constants.VARIATIONS[i][1], finalX, finalY, False))
                ap = pow(math.e, (len(current_sol) - len(next_sol)) / T)

                if ap > random.random():
                    current_sol = next_sol

            pos += 1
            T *= alpha

        end_time = timeit.default_timer()
        print("Simulated Annealing Time: {}".format(end_time - start_time))
        return min_sol

    def __searchSimulatedAnnealingV2(self, mapM, initialX, initialY, finalX, finalY):
        temperature = 1
        freezeTemperature = 0.0001
        alpha = 0.9
        iterationsNumber = 100

        while temperature > freezeTemperature:
            for i in range(iterationsNumber):
                pass

    def searchAStar(self):
        return self.__searchAStar(self.__map, self.__startX, self.__startY, 19, 0)

    def searchGreedy(self):
        return self.__searchGreedy(self.__map, self.__startX, self.__startY, 19, 0)

    def searchSimulatedAnnealing(self):
        return self.__searchSimulatedAnnealing(self.__map, self.__startX, self.__startY, 19, 0)

    def loadMap(self, path):
        # self.__map.randomMap()
        # self.__map.saveMap("resources/test1.map")
        self.__map.loadMap(path)

    def map(self):
        return self.__map

    def droneMove(self):
        self.__drone.move(self.__map)

    def mapWithDrone(self):
        return self.__drone.mapWithDrone(self.__map.image())

    def mapImage(self):
        return self.__map.image()
