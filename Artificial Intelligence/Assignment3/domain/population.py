from domain.individual import Individual


class Population:
    def __init__(self, generator, populationSize=0, individualSize=0):
        self.__populationSize = populationSize
        self.__individuals = [Individual(generator, individualSize) for _ in range(populationSize)]

    def evaluate(self, map):
        # evaluates the population
        for individual in self.__individuals:
            individual.findFitness(map)

    def selection(self, k=0):
        # perform a selection of k individuals from the population
        # and returns that selection
        pass
