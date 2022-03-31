from random import random
from domain.gene import Gene
from domain.map import Map
from utils.utils import START_POSITION, VARIATIONS


class Individual:
    def __init__(self, generator, size):
        self.__size = size
        self.__generator = generator
        self.__chromosome = [Gene(generator) for _ in range(self.__size)]
        self.__fitness = None

    @property
    def size(self):
        return self.__size

    @property
    def chromosome(self):
        return self.__chromosome

    @chromosome.setter
    def chromosome(self, other):
        self.__chromosome = other

    @property
    def fitness(self):
        return self.__fitness

    @fitness.setter
    def fitness(self, other):
        self.__fitness = other

    def __markTempMapUsingOriginalMap(self, startX, startY, tempMap, originalMap):
        markedCells = 0
        for variation in VARIATIONS:
            x = startX
            y = startY

            while originalMap.isValidCell(x, y):
                if tempMap.surface[x][y] != 2:
                    markedCells += 1

                tempMap.surface[x][y] = 2
                x += variation[0]
                y += variation[1]
        return markedCells

    def findFitness(self, map):
        # compute the fitness for the indivisual
        currentPosition = [START_POSITION[0], START_POSITION[1]]
        tempMap = Map()

        self.__fitness = self.__markTempMapUsingOriginalMap(currentPosition[0], currentPosition[1], tempMap, map)
        for index in range(self.__size):
            variation = VARIATIONS[self.__chromosome[index].value]
            currentPosition[0] += variation[0]
            currentPosition[1] += variation[1]

            if map.isValidCell(currentPosition[0], currentPosition[1]):
                self.__fitness += self.__markTempMapUsingOriginalMap(currentPosition[0], currentPosition[1], tempMap, map)
            else:
                break

    def mutate(self, mutateProbability=0.04):
        # perform a mutation with respect to the representation (with probability mutateProbability)
        if random() < mutateProbability:
            # select a random gene for mutation
            geneIndex = self.__generator.randint(0, len(self.__chromosome) - 1)
            # mutate the randomly selected gene
            self.__chromosome[geneIndex].value = self.__generator.randint(0, 3)

    def crossover(self, otherParent, crossoverProbability=0.8):
        # offspring1, offspring2 = Individual(self.__generator, self.__size), Individual(self.__generator, self.__size)
        offspring1 = self.__deepcopy__()
        offspring2 = otherParent.__deepcopy__()

        offspringChromosome1 = [None] * self.__size
        offspringChromosome2 = [None] * self.__size

        # perform the crossover between the self and the otherParent with probability crossoverProbability
        if random() < crossoverProbability:
            # perform uniform crossover
            for index in range(self.__size):
                if random() < 1 / 2:
                    offspringChromosome1[index] = self.__chromosome[index].__deepcopy__()
                    offspringChromosome2[index] = otherParent.chromosome[index].__deepcopy__()
                else:
                    offspringChromosome2[index] = self.__chromosome[index].__deepcopy__()
                    offspringChromosome1[index] = otherParent.chromosome[index].__deepcopy__()

            offspring1.chromosome = offspringChromosome1
            offspring2.chromosome = offspringChromosome2

        return offspring1, offspring2

    def __deepcopy__(self):
        newIndividual = Individual(self.__generator, self.__size)
        newIndividual.fitness = self.__fitness

        chromosome = [None] * self.__size
        for index in range(self.__size):
            chromosome[index] = self.__chromosome[index].__deepcopy__()

        newIndividual.chromosome = chromosome
        return newIndividual

    def __eq__(self, other):
        if self.__size != other.size:
            return False
        for index, gene in enumerate(self.__chromosome):
            if gene != other.chromosome[index]:
                return False
        return True
