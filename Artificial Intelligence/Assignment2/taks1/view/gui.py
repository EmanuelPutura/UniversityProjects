import pygame
import time

from pygame.locals import *
from taks1.utils.constants import Constants


class Gui:
    def __init__(self, controller):
        self.__controller = controller
        self.__screen = pygame.display.set_mode((400, 400))
        self.__screen.fill(Constants.WHITE)
        self.__load()

    def __displayWithPath(self, image, path):
        mark = pygame.Surface((20, 20))
        mark.fill(Constants.GREEN)
        for move in path:
            image.blit(mark, (move[1] * 20, move[0] * 20))

        return image

    def __load(self):
        self.__controller.loadMap("resources/test1.map")

        # initialize the pygame module
        pygame.init()
        # load and set the logo
        logo = pygame.image.load("resources/logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")

    def run(self):
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
                    self.__controller.droneMove()

            self.__screen.blit(self.__controller.mapWithDrone(), (0, 0))
            pygame.display.flip()

        # path = self.__controller.searchGreedy()
        # path = self.__controller.searchAStar()
        path = self.__controller.searchSimulatedAnnealing()
        self.__screen.blit(self.__displayWithPath(self.__controller.mapImage(), path), (0, 0))

        pygame.display.flip()
        time.sleep(5)
        pygame.quit()
