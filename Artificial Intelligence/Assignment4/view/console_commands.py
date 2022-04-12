from utils.utils import START_POSITION, MAP_LENGTH
from view.gui import movingDrone


class ConsoleCommands:
    def __init__(self, controller):
        self.__solutionPath = []
        self.__controller = controller

        self.__droneStartPosition = (0, 0)
        self.__droneEnergy = 10
        self.__sensors = [(1, 2), (6, 7), (15, 11), (10, 10), (19, 19)]

    def randomMapCommand(self):
        self.__controller.generateRandomMap()

    def loadMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.loadMap(filePath)

    def saveMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.saveMap(filePath)

    def displayMapCommand(self):
        movingDrone(self.__controller.getMap(), [START_POSITION], 0, False)

    def setDroneStartPositionCommand(self):
        startX = int(input("Please enter the X start coordinate of the drone ([0; : {}]): ".format(MAP_LENGTH - 1)))
        startY = int(input("Please enter the Y start coordinate of the drone ([0; : {}]): ".format(MAP_LENGTH - 1)))

        if not (0 <= startX < MAP_LENGTH and 0 <= startY < MAP_LENGTH):
            print("({}, {}) is not a valid drone position!".format(startX, startY))

        self.__droneStartPosition = (startX, startY)

        # TODO
        print(self.__droneStartPosition)

    def setDroneEnergyCommand(self):
        self.__droneEnergy = int(input("Please enter the energy level of the drone: "))

        # TODO
        print(self.__droneEnergy)

    def setSensorsPositionCommand(self):
        sensors = []
        sensorsNo = int(input("Please enter the number of sensors on the map: "))
        getCoordinates = lambda: (
            int(input("Please enter the X coordinate of the sensor ([0; : {}]): ".format(MAP_LENGTH - 1))),
            int(input("Please enter the Y coordinate of the sensor ([0; : {}]): ".format(MAP_LENGTH - 1)))
        )

        for _ in range(sensorsNo):
            (x, y) = getCoordinates()

            while not (0 <= x < MAP_LENGTH and 0 <= y < MAP_LENGTH):
                print("({}, {}) is not a valid drone position!".format(x, y))
                (x, y) = getCoordinates()

            sensors.append((x, y))

        self.__sensors = sensors

        # TODO
        print(self.__sensors)

    def runAlgorithmCommand(self):
        # TODO
        pass

    def showDronePathCommand(self):
        # TODO
        pass
