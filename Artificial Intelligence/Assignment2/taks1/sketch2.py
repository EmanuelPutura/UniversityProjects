# import the pygame module, so you can use it
import pickle
import pygame
import time
from random import random, randint
from queue import PriorityQueue

import numpy as np
from pygame.locals import *

# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

# define indexes variations
v = [[-1, 0], [1, 0], [0, 1], [0, -1]]


class Map:
    def __init__(self, n=20, m=20):
        self.n = n
        self.m = m
        self.surface = np.zeros((self.n, self.m))

    def randomMap(self, fill=0.2):
        for i in range(self.n):
            for j in range(self.m):
                if random() <= fill:
                    self.surface[i][j] = 1

    def __str__(self):
        string = ""
        for i in range(self.n):
            for j in range(self.m):
                string = string + str(int(self.surface[i][j]))
            string = string + "\n"
        return string

    def saveMap(self, numFile="test.map"):
        with open(numFile, 'wb') as f:
            pickle.dump(self, f)
            f.close()

    def loadMap(self, numfile):
        with open(numfile, "rb") as f:
            dummy = pickle.load(f)
            self.n = dummy.n
            self.m = dummy.m
            self.surface = dummy.surface
            f.close()

    def image(self):
        imagine = pygame.Surface((400, 400))
        brick = pygame.Surface((20, 20))
        brick.fill(BLUE)
        imagine.fill(WHITE)
        for i in range(self.n):
            for j in range(self.m):
                if self.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))

        return imagine


class Drone:
    def __init__(self, x, y):
        self.x = x
        self.y = y

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

    def mapWithDrone(self, mapImage):
        drona = pygame.image.load("drona.png")
        mapImage.blit(drona, (self.y * 20, self.x * 20))

        return mapImage


def manhattanDistance(x1, y1, x2, y2):
    return abs(x2 - x1) + abs(y2 - y1)


def searchAStar(mapM, droneD, initialX, initialY, finalX, finalY):
    distance = {}  # a map that associates, to each accessible vertex, the cost of the minimum cost walk from s to it
    previous = {}  # a map that maps each accessible vertex to its predecessor on a path from s to it
    pQueue = PriorityQueue()

    pQueue.put((manhattanDistance(initialX, initialY, finalX, finalY), (initialX, initialY)))
    distance[(initialX, initialY)] = 0
    found = False

    while not pQueue.empty() and not found:
        (_, current) = pQueue.get()
        for variation in [(0, -1), (1, 0), (0, 1), (-1, 0)]:
            neighbour = (current[0] + variation[0], current[1] + variation[1])
            if neighbour[0] < 0 or neighbour[0] > 19 or neighbour[1] < 0 or neighbour[1] > 19 or mapM.surface[neighbour[0]][neighbour[1]] == 1:
                continue

            if neighbour not in distance.keys() or distance[current] + 1 < distance[neighbour]:
                distance[neighbour] = distance[current] + 1
                pQueue.put((distance[neighbour] + manhattanDistance(neighbour[0], neighbour[1], finalX, finalY), neighbour))
                previous[neighbour] = current
        if current == (finalX, finalY):
            found = True

    if not found:
        return None

    current = distance[(finalX, finalY)]
    result = [None] * current
    result[current - 1] = previous[(finalX, finalY)]
    current -= 1

    while current > 0:
        result[current - 1] = previous[result[current]]
        current -= 1
    return result


def searchGreedy(mapM, droneD, initialX, initialY, finalX, finalY):
    found = False
    visited = []
    toVisit = PriorityQueue()
    toVisit.put((manhattanDistance(initialX, initialY, finalX, finalY), initialX, initialY))

    while not toVisit.empty() and not found:
        (_, nodeX, nodeY) = toVisit.get()
        visited.append((nodeX, nodeY))
        if (nodeX, nodeY) == (finalX, finalY):
            found = True

        # check neighbours of current node
        for variation in [(0, -1), (1, 0), (0, 1), (-1, 0)]:
            current = (nodeX + variation[0], nodeY + variation[1])
            if current not in visited and 0 <= current[0] <= 19 and 0 <= current[1] <= 19 and mapM.surface[current[0]][current[1]] != 1:
                toVisit.put((manhattanDistance(nodeX + variation[0], nodeY + variation[1], finalX, finalY),
                             nodeX + variation[0], nodeY + variation[1]))

    return None if not found else visited


def dummysearch():
    # example of some path in test1.map from [5,7] to [7,11]
    return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]


def displayWithPath(image, path):
    mark = pygame.Surface((20, 20))
    mark.fill(GREEN)
    for move in path:
        image.blit(mark, (move[1] * 20, move[0] * 20))

    return image


# define a main function
def main():
    # we create the map
    m = Map()
    # m.randomMap()
    # m.saveMap("test2.map")
    m.loadMap("test1.map")

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("Path in simple environment")

    # we position the drone somewhere in the area
    x = randint(0, 19)
    y = randint(0, 19)

    # create drona
    d = Drone(x, y)

    # create a surface on screen that has the size of 400 x 480
    screen = pygame.display.set_mode((400, 400))
    screen.fill(WHITE)

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

            if event.type == KEYDOWN:
                d.move(m)  # this call will be erased

        screen.blit(d.mapWithDrone(m.image()), (0, 0))
        pygame.display.flip()

    path = searchAStar(m, d, x, y, 19, 0)
    screen.blit(displayWithPath(m.image(), path), (0, 0))

    pygame.display.flip()
    time.sleep(5)
    pygame.quit()


# run the main function only if this module is executed as the main script
# (if you import this as a module then nothing is executed)
if __name__ == "__main__":
    # call the main function
    main()
