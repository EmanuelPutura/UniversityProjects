import pickle
from domain.map import Map
from domain.population import Population
from utils.generator import RandomGenerator


class Repository:
    def __init__(self):
        self.__map = Map()
        self.__population = None

    @property
    def map(self):
        return self.__map

    @property
    def population(self):
        return self.__population

    def createPopulation(self, populationSize, individualSize):
        self.__population = Population(RandomGenerator(), populationSize, individualSize)
        return self.__population

    def saveMap(self, filePath):
        with open(filePath, 'wb') as file:
            pickle.dump(self.__map, file)

    def loadMap(self, filePath):
        with open(filePath, "rb") as file:
            fileMap = pickle.load(file)
            self.__map = fileMap
            file.close()
