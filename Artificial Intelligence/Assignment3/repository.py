import pickle
from domain import *


class Repository:
    def __init__(self):
        self.__populations = []
        self.__map = Map()
        
    def createPopulation(self, populationSize, individualSize):
        return Population(populationSize, individualSize)
        
    # TO DO : add the other components for the repository: 
    #    load and save from file, etc
