# import the pygame module, so you can use it
import pickle
import pygame
import time

from random import randint

from pygame.locals import *

from taks1.domain.drone import Drone
from taks1.domain.map import Map
from taks1.utils.constants import Constants


def displayWithPath(image, path):
    mark = pygame.Surface((20, 20))
    mark.fill(Constants.GREEN)
    for move in path:
        image.blit(mark, (move[1] * 20, move[0] * 20))

    return image


# define a main function
def main():
    # we create the map
    m = Map()
    # m.randomMap()
    # m.saveMap("test2.map")
    m.loadMap("resources/test1.map")

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("resources/logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("Path in simple environment")

    # we position the drone somewhere in the area
    x = randint(0, 19)
    y = randint(0, 19)

    # create drona
    d = Drone(x, y)

    # create a surface on screen that has the size of 400 x 480
    screen = pygame.display.set_mode((400, 400))
    screen.fill(Constants.WHITE)

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
