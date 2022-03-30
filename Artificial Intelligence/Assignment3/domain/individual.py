from random import random
from domain.gene import Gene


class Individual:
    def __init__(self, size=0):
        self.__size = size
        self.__x = [Gene() for i in range(self.__size)]
        self.__f = None

    def fitness(self):
        # compute the fitness for the indivisual
        # and save it in self.__f
        pass

    def mutate(self, mutateProbability=0.04):
        if random() < mutateProbability:
            pass
            # perform a mutation with respect to the representation

    def crossover(self, otherParent, crossoverProbability=0.8):
        offspring1, offspring2 = Individual(self.__size), Individual(self.__size)
        if random() < crossoverProbability:
            pass
            # perform the crossover between the self and the otherParent

        return offspring1, offspring2
