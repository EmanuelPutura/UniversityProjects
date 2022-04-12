import pickle
from domain.map import Map


class Repository:
    def __init__(self):
        self.__map = Map()

    @property
    def map(self):
        return self.__map

    def saveMap(self, filePath):
        with open(filePath, 'wb') as file:
            pickle.dump(self.__map, file)

    def loadMap(self, filePath):
        with open(filePath, "rb") as file:
            fileMap = pickle.load(file)
            self.__map = fileMap
            file.close()
