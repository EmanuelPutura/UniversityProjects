from utils.generator import RandomGenerator
from utils.utils import MAX_ITERATIONS, START_POSITION, VARIATIONS


class Controller:
    def __init__(self, repository, randomGenerator):
        self.__repository = repository
        self.__populationSize = None
        self.__individualSize = None
        self.__randomGenerator = randomGenerator

    def generateRandomMap(self):
        self.__repository.map.randomMap()

    def saveMap(self, filePath):
        self.__repository.saveMap(filePath)

    def loadMap(self, filePath):
        self.__repository.loadMap(filePath)

    def getMap(self):
        return self.__repository.map

    def __getSolutionPath(self, solutionIndividual):
        (currentX, currentY) = START_POSITION
        solutionVariations = solutionIndividual.chromosome

        for index, gene in enumerate(solutionVariations):
            solutionVariations[index] = VARIATIONS[gene.value]

        solutionPath = [(currentX, currentY)]
        for variation in solutionVariations:
            currentX += variation[0]
            currentY += variation[1]

            if not self.__repository.map.isValidCell(currentX, currentY):
                break

            solutionPath.append((currentX, currentY))
        return solutionPath

    def __iteration(self):
        # a iteration:
        # selection of the parents
        # create offsprings by crossover of the parents
        # apply some mutations
        # selection of the survivors

        parent1, parent2 = self.__repository.population.crossoverSelection(False)  # select two parents for crossover operation
        offspring1, offspring2 = parent1.crossover(parent2)  # perform the crossover

        # perform mutations with a predefined probability
        offspring1.mutate()
        offspring2.mutate()

        offspring1.findFitness(self.__repository.map)
        offspring2.findFitness(self.__repository.map)

        # select the survivors
        self.__repository.population.survivorsSelection(offspring1, offspring2)

    def run(self):
        # until stop condition
        #    perform an iteration
        #    save the information need it for the satistics
        # return the results and the info for statistics

        self.__repository.population.evaluate(self.getMap())
        averageFitness = [self.__repository.population.computeAverageFitness()]

        for i in range(MAX_ITERATIONS):
            self.__iteration()
            averageFitness.append(self.__repository.population.computeAverageFitness())

        self.__repository.population.evaluate(self.getMap())
        bestIndividual = self.__repository.population.individuals[0]

        for individual in self.__repository.population.individuals:
            if individual.fitness > bestIndividual.fitness:
                bestIndividual = individual

        return bestIndividual, averageFitness

    def solver(self, populationSize, individualSize):
        # create the population
        # run the algorithm
        # return the results and the statistics

        self.__populationSize = populationSize
        self.__individualSize = individualSize

        self.__repository.createPopulation(self.__randomGenerator, self.__populationSize, self.__individualSize)

        (solution, averageFitness) = self.run()

        return self.__getSolutionPath(solution), averageFitness, solution
