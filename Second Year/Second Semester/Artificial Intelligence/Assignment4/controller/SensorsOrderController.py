from queue import PriorityQueue

from domain.ant import Ant
from domain.cell_numeric_representation import CellNumericRepresentation
from domain.sensor import Sensor
from utils.utils import VARIATIONS, DRONE_START

import random


class SensorsOrderController:
    def __init__(self, repository):
        self.__repository = repository
        self.__populationSize = None
        self.__individualSize = None
        self.__sensorsPath = None

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
    def determineMaxDiscoveredCells(self, sensor, energyLevel, returnPositions=False):
        discoveredCellsInDirection = [0] * len(VARIATIONS)
        index = 0
        positions = []

        for variation in VARIATIONS:
            currentX = sensor.x + variation[0]
            currentY = sensor.y + variation[1]
            currentDiscoveredCells = 0

            while currentDiscoveredCells < energyLevel and self.__repository.map.isValidCell(currentX, currentY):
                positions.append((currentX, currentY))

                currentDiscoveredCells += 1
                currentX += variation[0]
                currentY += variation[1]

            discoveredCellsInDirection[index] = currentDiscoveredCells
            index += 1

        if returnPositions:
            return sum(discoveredCellsInDirection), positions
        return sum(discoveredCellsInDirection)

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

    def __updatePheromoneTrace(self, ants, pheromoneEvaporationCoefficient, trace):
        antAddedPheromone = [1.0 / ants[i].fitness for i in range(len(ants))]

        # pheromone evaporation
        for i in range(CellNumericRepresentation.NUMERIC_REPRESENTATION_SUPREMUM + 1):
            for j in range(CellNumericRepresentation.NUMERIC_REPRESENTATION_SUPREMUM + 1):
                trace[i][j] *= (1 - pheromoneEvaporationCoefficient)

        # update pheromone trace
        for i in range(len(ants)):
            for j in range(len(ants[i].sensorsPath) - 1):
                sensor1 = ants[i].sensorsPath[j]
                sensor1NumericRepresentation = CellNumericRepresentation.numericRepresentation(sensor1.x, sensor1.y)
                sensor2 = ants[i].sensorsPath[j + 1]
                sensor2NumericRepresentation = CellNumericRepresentation.numericRepresentation(sensor2.x, sensor2.y)

                trace[sensor1NumericRepresentation][sensor2NumericRepresentation] += antAddedPheromone[i]

    def __antNextSensor(self, ant, trace, bestChoiceProbability, alpha, beta):
        possibleNextSensors = list(set(self.__repository.map.sensors) - set(ant.sensorsPath))
        if not possibleNextSensors:
            return False

        lastSensor = ant.sensorsPath[-1]
        toAddResult = self.__nextSensor(possibleNextSensors, lastSensor, trace, bestChoiceProbability, alpha, beta)
        ant.addSensor(toAddResult[0], toAddResult[1])

    def __nextSensor(self, possibleNextSensors, lastSensor, trace, bestChoiceProbability, alpha, beta):
        probabilities = [
            (1.0 / len(self.minimumDistanceBetween(lastSensor.x, lastSensor.y, possibleNextSensors[i].x,
                                                   possibleNextSensors[i].y))) ** beta *
            trace[CellNumericRepresentation.numericRepresentation(lastSensor.x, lastSensor.y)][
                CellNumericRepresentation.numericRepresentation(
                    possibleNextSensors[i].x, possibleNextSensors[i].y)] ** alpha
            for i in range(len(possibleNextSensors))
        ]

        if random.random() < bestChoiceProbability:
            # add best possible move
            possibleMoves = [(i, probabilities[i]) for i in range(len(probabilities))]
            bestMove = max(possibleMoves, key=lambda e: e[1])
            return possibleNextSensors[bestMove[0]], len(self.minimumDistanceBetween(lastSensor.x, lastSensor.y, possibleNextSensors[bestMove[0]].x,
                    possibleNextSensors[bestMove[0]].y))
        else:
            # add with a certain probability one of the possible sensors
            probabilitiesSum = sum(probabilities)
            if probabilitiesSum == 0:
                return random.choice(possibleNextSensors)

            probabilities = [probabilities[i] / probabilitiesSum for i in range(len(probabilities))]
            chosenSensor = random.choices(possibleNextSensors, probabilities, k=1)[0]
            return chosenSensor, len(self.minimumDistanceBetween(lastSensor.x, lastSensor.y, chosenSensor.x, chosenSensor.y))

    def antsEpoch(self, trace, antsNumber, alpha, beta, bestChoiceProbability, pheromoneEvaporationCoefficient):
        sensors = self.__repository.map.sensors
        ants = []

        # build the ants with the first visited sensor randomly chosen
        for _ in range(antsNumber):
            toAddResult = self.__nextSensor(sensors, Sensor(DRONE_START[0], DRONE_START[1]), trace, bestChoiceProbability, alpha, beta)
            ants.append(Ant(toAddResult[0], toAddResult[1]))

        # the length of an ant solution is equal to the number of sensors
        for _ in range(len(sensors)):
            for ant in ants:
                self.__antNextSensor(ant, trace, bestChoiceProbability, alpha, beta)

        # update the pheromone trace
        self.__updatePheromoneTrace(ants, pheromoneEvaporationCoefficient, trace)

        # return the best ant sensors path
        solutions = [(ants[i].fitness, i) for i in range(len(ants))]
        bestSolution = max(solutions)
        return ants[bestSolution[1]]

    def __buildSolutionPath(self, solutionSensors):
        if not solutionSensors:
            return []

        solution = self.minimumDistanceBetween(DRONE_START[0], DRONE_START[1], solutionSensors[0].x, solutionSensors[0].y)
        for i in range(1, len(solutionSensors)):
            solution += self.minimumDistanceBetween(solutionSensors[i - 1].x, solutionSensors[i - 1].y, solutionSensors[i].x, solutionSensors[i].y)

        solution.append((solutionSensors[-1].x, solutionSensors[-1].y))
        return solution

    def __getEnergyConsumedByEachSensor(self, sensorsPath, availableDroneEnergy):
        # sensorsEnergyAndDiscoveredCells[i] = (a, b), where a - energy given to ith sensor, b - discovered cells by ith sensor, being given a energy points
        sensorsEnergyAndDiscoveredCells = [[0, 0] for _ in range(len(sensorsPath))]

        for energyPoint in range(1, availableDroneEnergy + 1):
            newDiscoveredCells = []  # newDiscoveredCells[i] = (sensor index, number of new cells discovered by sensor i by adding one energy point to it)
            for i in range(len(sensorsEnergyAndDiscoveredCells)):
                energySoFar = sensorsEnergyAndDiscoveredCells[i][0]
                if energySoFar >= 5:
                    newDiscoveredCells.append((i, -1))
                    continue

                discoveredSoFar = sensorsEnergyAndDiscoveredCells[i][1]
                newDiscoveredCells.append((i, self.determineMaxDiscoveredCells(sensorsPath[i], 1 + energySoFar) - discoveredSoFar))

            (winningSensorIndex, sensorNewDiscoveredCells) = max(newDiscoveredCells, key=lambda el: el[1])
            if sensorNewDiscoveredCells == -1:
                break

            sensorsEnergyAndDiscoveredCells[winningSensorIndex][0] += 1
            sensorsEnergyAndDiscoveredCells[winningSensorIndex][1] += sensorNewDiscoveredCells

        return [(sensorsPath[i], sensorsEnergyAndDiscoveredCells[i][0]) for i in range(len(sensorsPath))]

    def getDisocveredCellsPositions(self, availableEnergy):
        energyConsumedBySensor = self.__getEnergyConsumedByEachSensor(self.__sensorsPath, availableEnergy)

        discoveredCells = []
        for (sensor, energy) in energyConsumedBySensor:
            discoveredCells += self.determineMaxDiscoveredCells(sensor, energy, True)[1]

        return discoveredCells

    def solve(self, epochsNumber, antsNumber, alpha, beta, bestChoiceProbability, pheromoneEvaporationCoefficient):
        trace = [[1 for _ in range(CellNumericRepresentation.NUMERIC_REPRESENTATION_SUPREMUM + 1)] for _ in range(CellNumericRepresentation.NUMERIC_REPRESENTATION_SUPREMUM + 1)]
        bestSolution = None

        for _ in range(epochsNumber):
            solution = self.antsEpoch(trace, antsNumber, alpha, beta, bestChoiceProbability, pheromoneEvaporationCoefficient)

            if not bestSolution or bestSolution.fitness > solution.fitness:
                bestSolution = solution

        solutionPath = self.__buildSolutionPath(bestSolution.sensorsPath)
        self.__sensorsPath = bestSolution.sensorsPath

        return solutionPath, len(solutionPath)
