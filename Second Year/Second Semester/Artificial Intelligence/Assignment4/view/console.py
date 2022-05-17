"""
create a menu
  1. map options:
        a. create random map
        b. load a map
        c. save a map
        d. visualise map
  2. EA options:
        a. parameters setup
        b. run the solver
        c. visualise the statistics
        d. view the drone moving on a path
             function gui.movingDrone(currentMap, path, speed, markseen)
             ATENTION! the function doesn't check if the path passes trough walls
"""
from view.console_commands_sensors_order import ConsoleCommandsSensorsOrder
from view.console_commands_sensors_order_energy import ConsoleCommandsSensorsOrderEnergy


class Console:
    def __init__(self, controller):
        self.__running = False
        self.__controller = controller

        self.__consoleCommands = ConsoleCommandsSensorsOrder(controller)
        # self.__consoleCommands = ConsoleCommandsSensorsOrderEnergy(controller)

        self.__commands = {
            "map.random": self.__consoleCommands.randomMapCommand,
            "map.load": self.__consoleCommands.loadMapCommand,
            "map.save": self.__consoleCommands.saveMapCommand,
            "map.display": self.__consoleCommands.displayMapCommand,
            "alg.sensors": self.__consoleCommands.setSensorsPositionCommand,
            "alg.run": self.__consoleCommands.runAlgorithmCommand,
            "alg.drone": self.__consoleCommands.showDronePathCommand
        }

    def printMenu(self):
        print("-" * 100)
        print("Map options:")
        print("- map.random: create a random map")
        print("- map.load: load map from a file")
        print("- map.save: save current map to a file")
        print("- map.display: visualize the map")
        print("Algorithm options:")
        print("- alg.sensors: set the position of the sensors")
        print("- alg.run: run the algorithm")
        print("- alg.drone: view the drone moving on a path")
        print("Other commands:")
        print("- exit: exit the application")
        print("-" * 100)

    def run(self):
        self.__running = True
        while self.__running:
            self.printMenu()
            command = input(">> ")
            if command == "exit":
                self.__running = False
                break
            elif command not in self.__commands:
                print("'{}' is not a valid command!".format(command))
                continue

            self.__commands[command]()

            # try:
            #     self.__commands[command]()
            # except Exception as error:
            #     print("Error: {}".format(str(error)))
