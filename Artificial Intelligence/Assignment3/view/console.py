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
from utils.utils import START_POSITION
from view.console_commands import ConsoleCommands


class Console:
    def __init__(self, controller):
        self.__running = False
        self.__controller = controller

        self.__consoleCommands = ConsoleCommands(controller)
        self.__commands = {
            "map.random": self.__consoleCommands.randomMapCommand,
            "map.load": self.__consoleCommands.loadMapCommand,
            "map.save": self.__consoleCommands.saveMapCommand,
            "map.display": self.__consoleCommands.displayMapCommand,
            "ea.setup": self.__consoleCommands.eaSetupCommand,
            "ea.run": self.__consoleCommands.eaRunCommand,
            "ea.statistics": self.__consoleCommands.eaStatisticsCommand,
            "ea.drone": self.__consoleCommands.eaDroneCommand
        }

    def printMenu(self):
        print("-" * 100)
        print("Map options:")
        print("- map.random: create a random map")
        print("- map.load: load map from a file")
        print("- map.save: save current map to a file")
        print("- map.display: visualize the map")
        print("Evolutionary algorithm options:")
        print("- ea.setup: parameters setup")
        print("- ea.run: run the solver")
        print("- ea.statistics: visualize the statistics")
        print("- ea.drone: view the drone moving on a path")
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
