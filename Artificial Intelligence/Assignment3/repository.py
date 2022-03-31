import pickle
from Domain import *
from Domain.map import Map
from Domain.population import Population


class Repository:
    def __init__(self):
        self.__populations = []
        self.__map = Map()

    @property
    def map(self):
        return self.__map

    @property
    def populations(self):
        return self.__populations

    def createPopulation(self, populationSize, individualSize):
        return Population(populationSize, individualSize)
        
    # TO DO : add the other components for the repository: 
    #    load and save from file, etc
