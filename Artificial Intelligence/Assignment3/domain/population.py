"""
    The problem uses a Steady-state Evolutionary Algorithm
    (i.e., each generation creates two offsprings, which replace the same amount of parents which are worse than them)
"""
from random import random, randint
from domain.individual import Individual
from utils.utils import START_POSITION


class PopulationError(Exception):
    def __init__(self, message):
        super().__init__(message)


class Population:
    def __init__(self, generator, populationSize=2, individualSize=0):
        if populationSize < 2:
            raise PopulationError("Populations size must be greater than or equal to two!")

        self.__populationSize = populationSize
        self.__individuals = [Individual(generator, individualSize) for _ in range(populationSize)]

    @property
    def individuals(self):
        return self.__individuals

    def evaluate(self, map):
        # evaluates the population
        for individual in self.__individuals:
            individual.findFitness(map)

    def survivorsSelection(self, offspring1, offspring2):
        # selects the survivors for the next generation
        worstParent = self.__individuals[0]
        secondWorstParent = self.__individuals[1]

        for individual in self.__individuals:
            if individual.fitness < worstParent.fitness:
                secondWorstParent = worstParent
                worstParent = individual
            elif individual.fitness < secondWorstParent.fitness:
                secondWorstParent = individual

        (worstOffspring, secondWorstOffspring) = (offspring1, offspring2) if offspring1.fitness < offspring2.fitness else (offspring2, offspring1)

        if secondWorstOffspring.fitness < worstParent.fitness:
            return
        elif secondWorstParent.fitness <= secondWorstOffspring.fitness and worstParent.fitness <= worstOffspring.fitness:
            self.__individuals[0] = worstOffspring
            self.__individuals[1] = secondWorstOffspring
        elif worstOffspring.fitness < worstParent.fitness:
            self.__individuals[0] = secondWorstOffspring

    def crossoverSelection(self, random=False):
        # perform a random selection
        if random:
            return self.__individuals[randint(0, self.__populationSize - 1)], self.__individuals[randint(0, self.__populationSize - 1)]

        # peform a ranking selection
        # i.e., perform a roulette algorithm taking into account the rank instead of the fitness
        self.__individuals.sort(key=lambda individual: individual.fitness)
        ranksSum = self.__populationSize * (self.__populationSize + 1) / 2
        probabilities = []

        for index in range(self.__populationSize):
            probabilities.append((index + 1) / ranksSum)

        parentIndex1 = self.__getSelectedIndex(probabilities)
        parentIndex2 = None

        while parentIndex2 != parentIndex1:
            parentIndex2 = self.__getSelectedIndex(probabilities)
        return self.__individuals[parentIndex1], self.__individuals[parentIndex2]

    """
        Let probabilities = [a1, a2, a3, ..., ak], where ai is in [0, 1], i = 1,k 
        Consider then the list ranges = [0, a1, a1 + a2, a1 + a2 + a3, ..., a1 + a2 + ... + ak = 1]
        Now we generate a number between 0 and 1, generatedValue.
        Suppose generatedValue is in the interval [a1 + ... + ai, a1 + ... + aj], with i < j. Then, the selected index is i - 1
        (subtract 1 because we index the list from zero)
    """
    def __getSelectedIndex(self, probabilities):
        if not len(probabilities):
            return

        generatedValue = random()
        currentSum = 0
        ranges = [0]

        for index in range(self.__populationSize):
            currentSum += probabilities[index]
            ranges.append(currentSum)

            if generatedValue <= ranges[-1]:
                return index
        return self.__populationSize - 1
