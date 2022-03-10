from Domain.drone import Drone
from Domain.environment import Environment
from Domain.map import DetectedMap


class Controller:
    def __init__(self):
        # we create the environment
        self.__environment = Environment()
        self.__environment.randomMap()
        # self.__environment.loadMapFromTxt("Resources/Files/test.txt")

        # we create the map
        self.__map = DetectedMap()

        # we position the drone somewhere in the area
        (x, y) = self.__environment.randomEmptyPosition()
        # (x, y) = (2, 0)

        # creaate drone
        self.__drone = Drone(x, y)

    def environmentImage(self):
        return self.__environment.image()

    def mapImage(self):
        return self.__map.image(self.__drone.x, self.__drone.y)

    def move(self):
        self.__drone.moveDFS(self.__map, self.__environment)

        if self.__drone.x is not None and self.__drone.y is not None:
            self.__map.markDetectedWalls(self.__environment, self.__drone.x, self.__drone.y)
            return self.__drone.x, self.__drone.y
        return None
