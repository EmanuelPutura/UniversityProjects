class Controller:
    def __init__(self, repository):
        self.__repository = repository
        self.__populationSize = None
        self.__individualSize = None

    def generateRandomMap(self):
        self.__repository.map.randomMap()

    def saveMap(self, filePath):
        self.__repository.saveMap(filePath)

    def loadMap(self, filePath):
        self.__repository.loadMap(filePath)

    def getMap(self):
        return self.__repository.map

    def solve(self):
        pass
