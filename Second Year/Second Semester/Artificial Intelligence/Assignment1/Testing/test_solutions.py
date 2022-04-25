from Domain.drone import Drone
from Domain.environment import Environment
from Domain.map import DetectedMap


class Testing:
    @staticmethod
    def testSolution(environment, start_x, start_y, optimize):
        map = DetectedMap()
        drone = Drone(start_x, start_y)

        cnt = 0
        while drone.x is not None and drone.y is not None:
            map.markDetectedWalls(environment, drone.x, drone.y)
            drone.moveDFS(map, environment, optimize)
            cnt += 1

        print("Result of the test, with optimization: {} - {} moves".format(optimize, cnt))

    @staticmethod
    def testGenericSolution():
        environment = Environment()
        environment.randomMap()
        (x, y) = environment.randomEmptyPosition()

        Testing.testSolution(environment, x, y, False)
        Testing.testSolution(environment, x, y, True)
