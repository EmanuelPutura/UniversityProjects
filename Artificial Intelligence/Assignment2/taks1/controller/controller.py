from queue import PriorityQueue
from taks1.utils.constants import Constants


class Controller:
    def __init__(self):
        pass

    def __manhattanDistance(self, x1, y1, x2, y2):
        return abs(x2 - x1) + abs(y2 - y1)

    def dummysearch(self):
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]

    def searchAStar(self, mapM, droneD, initialX, initialY, finalX, finalY):
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
        return result

    def searchGreedy(self, mapM, droneD, initialX, initialY, finalX, finalY):
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

        return None if not found else visited
