# import the pygame module, so you can use it
import pickle
import time

import pygame
from random import random, randint

import numpy as np
from pygame.locals import *

# creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# define directions
LEFT = 0
RIGHT = 2
DOWN = 1
UP = 3

# sleeping time in seconds before performing DFS
SLEEPING_TIME = 0.2

# filling factor of the environment
FILL_FACTOR = 0.25

# define indexes variations
variations = [[-1, 0], [1, 0], [0, 1], [0, -1]]
direction_variations_mapping = {(-1, 0): LEFT, (1, 0): RIGHT, (0, -1): UP, (0, 1): DOWN}


class Environment:
    def __init__(self):
        self.__n = 20
        self.__m = 20
        self.__surface = np.zeros((self.__n, self.__m))

    def randomMap(self, fill=FILL_FACTOR):
        for i in range(self.__n):
            for j in range(self.__m):
                if random() <= fill:
                    self.__surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.__n):
            for j in range(self.__m):
                string = string + str(int(self.__surface[i][j]))
            string = string + "\n"
        return string

    def readUDMSensors(self, x, y):
        readings = [0, 0, 0, 0]
        # UP 
        xf = x - 1
        while (xf >= 0) and (self.__surface[xf][y] == 0):
            xf = xf - 1
            readings[LEFT] = readings[LEFT] + 1
        # DOWN
        xf = x + 1
        while (xf < self.__n) and (self.__surface[xf][y] == 0):
            xf = xf + 1
            readings[RIGHT] = readings[RIGHT] + 1
        # LEFT
        yf = y + 1
        while (yf < self.__m) and (self.__surface[x][yf] == 0):
            yf = yf + 1
            readings[DOWN] = readings[DOWN] + 1
        # RIGHT
        yf = y - 1
        while (yf >= 0) and (self.__surface[x][yf] == 0):
            yf = yf - 1
            readings[UP] = readings[UP] + 1

        return readings

    def saveEnvironment(self, num_file):
        with open(num_file, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def loadEnvironment(self, num_file):
        with open(num_file, "rb") as f:
            dummy = pickle.load(f)
            self.__n = dummy.__n
            self.__m = dummy.__m
            self.__surface = dummy.__surface
            f.close()

    def image(self, colour=BLUE, background=WHITE):
        imagine = pygame.Surface((420, 420))
        brick = pygame.Surface((20, 20))
        brick.fill(BLUE)
        imagine.fill(WHITE)
        for i in range(self.__n):
            for j in range(self.__m):
                if self.__surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))

        return imagine

    def randomEmptyPosition(self):
        x = randint(0, 19)
        y = randint(0, 19)

        while self.__surface[x][y] != 0:
            x = randint(0, 19)
            y = randint(0, 19)
        return x, y


class DMap:
    def __init__(self):
        self.__n = 20
        self.__m = 20
        self.surface = np.zeros((self.__n, self.__m))
        for i in range(self.__n):
            for j in range(self.__m):
                self.surface[i][j] = -1

    def markDetectedWalls(self, e, x, y):
        # TODO
        # mark on this map the walls that you detect
        walls = e.readUDMSensors(x, y)
        i = x - 1
        if walls[LEFT] > 0:
            while (i >= 0) and (i >= x - walls[LEFT]):
                self.surface[i][y] = 0
                i = i - 1
        if i >= 0:
            self.surface[i][y] = 1

        i = x + 1
        if walls[RIGHT] > 0:
            while (i < self.__n) and (i <= x + walls[RIGHT]):
                self.surface[i][y] = 0
                i = i + 1
        if i < self.__n:
            self.surface[i][y] = 1

        j = y + 1
        if walls[DOWN] > 0:
            while (j < self.__m) and (j <= y + walls[DOWN]):
                self.surface[x][j] = 0
                j = j + 1
        if j < self.__m:
            self.surface[x][j] = 1

        j = y - 1
        if walls[UP] > 0:
            while (j >= 0) and (j >= y - walls[UP]):
                self.surface[x][j] = 0
                j = j - 1
        if j >= 0:
            self.surface[x][j] = 1

        return None

    def image(self, x, y):

        imagine = pygame.Surface((420, 420))
        brick = pygame.Surface((20, 20))
        empty = pygame.Surface((20, 20))
        empty.fill(WHITE)
        brick.fill(BLACK)
        imagine.fill(GRAYBLUE)

        for i in range(self.__n):
            for j in range(self.__m):
                if self.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))
                elif self.surface[i][j] == 0:
                    imagine.blit(empty, (j * 20, i * 20))

        drona = pygame.image.load("drona.png")
        imagine.blit(drona, (y * 20, x * 20))
        return imagine


class Drone:
    def __init__(self, x, y):
        self.x = x
        self.y = y

        self.__dfs_visited = set()
        self.__dfs_parents = dict()
        self.__dfs_stack = [(x, y)]
        self.__backtrack = False

    def move(self, detectedMap):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detectedMap.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detectedMap.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detectedMap.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detectedMap.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def __isValidIndex(self, x, y, detectedMap):
        return 0 <= x <= 19 and 0 <= y <= 19 and detectedMap.surface[x][y] != 1

    def moveDFS(self, detectedMap, environment):
        if not self.__dfs_stack:
            self.x, self.y = None, None
            return
        # if self.__backtrack:
        #     self.__doBacktrack()
        #     # if self.__backtrack:
        #     #     return

        top = self.__dfs_stack.pop()
        while top in self.__dfs_visited:
            if not self.__dfs_stack:
                self.x, self.y = None, None
                return
            top = self.__dfs_stack.pop()

        self.__dfs_visited.add(top)
        self.x = top[0]
        self.y = top[1]

        sensors_data = environment.readUDMSensors(top[0], top[1])
        added_neighbours = 0

        for variation in variations:
            if sensors_data[direction_variations_mapping[(variation[0], variation[1])]] == 0:
                continue

            current = (top[0] + variation[0], top[1] + variation[1])
            if self.__isValidIndex(current[0], current[1], detectedMap) and (current[0] != self.x or current[1] != self.y):
                # TODO optimization in adding new graph nodes to the stack
                if current not in self.__dfs_visited:
                    self.__dfs_stack.append(current)
                    self.__dfs_parents[current] = top
                    added_neighbours += 1

        # if added_neighbours == 0:
        #     self.__backtrack = True
        #     self.__doBacktrack()
        #     # if not self.__backtrack:
        #     #     self.moveDFS(detectedMap, environment)
        # else:
        #     self.__backtrack = False

    def __doBacktrack(self):
        if not self.__dfs_stack:
            self.x, self.y = None, None
            self.__backtrack = False
            return

        current = (self.x, self.y)
        common_parent = self.__dfs_parents[self.__dfs_stack[-1]]
        if current != common_parent:
            self.x, self.y = self.__dfs_parents[current]
        else:
            self.__backtrack = False


# define a main function
def main():
    # we create the environment
    environment = Environment()
    # e.loadEnvironment("test2.map")
    environment.randomMap()
    # print(str(e))

    # we create the map
    map = DMap()

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration")

    # we position the drone somewhere in the area
    # x = randint(0, 19)
    # y = randint(0, 19)
    (x, y) = environment.randomEmptyPosition()

    # creaate drone
    drone = Drone(x, y)

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode((800, 400))
    screen.fill(WHITE)
    screen.blit(environment.image(), (0, 0))

    # define a variable to control the main loop
    running = True

    # main loop
    while running:
        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False
            # if event.type == KEYDOWN:
            #     # use this function instead of move
            #     d.moveDFS(m)
            #     # d.move(m)

        time.sleep(SLEEPING_TIME)
        last_x, last_y = drone.x, drone.y
        drone.moveDFS(map, environment)

        if drone.x is not None and drone.y is not None:
            map.markDetectedWalls(environment, drone.x, drone.y)
            screen.blit(map.image(drone.x, drone.y), (400, 0))
        elif last_x is not None and last_y is not None:
            # final_cell = pygame.Surface((20, 20))
            # final_cell.fill(GREEN)
            # map_image = m.image(last_x, last_y)
            # map_image.blit(final_cell, (last_y * 20, last_x * 20))
            # screen.blit(map_image, (400, 0))
            pass
        pygame.display.flip()

    pygame.quit()


# run the main function only if this module is executed as the main script
# (if you import this as a module then nothing is executed)
if __name__ == "__main__":
    # call the main function
    main()
