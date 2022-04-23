from utils.utils import MAP_LENGTH, DRONE_START, DRONE_ENERGY, SENSORS, EPOCHS_NUMBER, ANTS_NUMBER, \
    EVAPORATION_COEFFICIENT, BEST_CHOICE_PROBABILITY, BETA, ALPHA
from view.gui import movingDrone


class ConsoleCommands:
    def __init__(self, controller):
        self.__solutionPath = []
        self.__controller = controller

        self.__droneEnergy = DRONE_ENERGY
        self.__sensors = SENSORS
        self.__solutionPath = None

    def randomMapCommand(self):
        self.__controller.generateRandomMap()

    def loadMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.loadMap(filePath)

    def saveMapCommand(self):
        filePath = input("Please enter the file path: ")
        self.__controller.saveMap(filePath)

    def displayMapCommand(self):
        movingDrone(self.__controller.getMap(), [DRONE_START], 0, False)

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

            while not (0 <= x < MAP_LENGTH and 0 <= y < MAP_LENGTH and (x != DRONE_START[0] or y != DRONE_START[1])):
                print("({}, {}) is not a valid sensor coordinate!".format(x, y))
                (x, y) = getCoordinates()

            sensors.append((x, y))

        self.__sensors = sensors
        self.__controller.setSensors(self.__sensors)

    def runAlgorithmCommand(self):
        # TODO
        print("The algorithm started, it might take a while to finish running...")
        self.__solutionPath = self.__controller.solve(EPOCHS_NUMBER, ANTS_NUMBER, ALPHA, BETA, BEST_CHOICE_PROBABILITY, EVAPORATION_COEFFICIENT)

    def showDronePathCommand(self):
        # TODO
        if not self.__solutionPath:
            print("You must first run the ACO algorithm!")
            return

        movingDrone(self.__controller.getMap(), self.__solutionPath, 0.3, False)
