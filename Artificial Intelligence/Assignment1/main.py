# import the pygame module, so you can use it
import time

import pygame

from Testing.test_solutions import Testing
from Controller.controller import Controller
from Utils.constants import Constants


# define a main function
def main():
    Testing.testGenericSolution()
    controller = Controller()

    # initialize the pygame module
    pygame.init()

    # load and set the logo
    logo = pygame.image.load("Resources/Images/logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("Drone Exploration")

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode((Constants.BOARD_DIM * Constants.CELL_SIZE * 2, Constants.BOARD_DIM * Constants.CELL_SIZE))
    screen.fill(Constants.WHITE)
    screen.blit(controller.environmentImage(), (0, 0))

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
            #     d.move(m)

        time.sleep(Constants.SLEEPING_TIME)
        res = controller.move()

        if res is not None:
            screen.blit(controller.mapImage(), (Constants.BOARD_DIM * Constants.CELL_SIZE, 0))
        pygame.display.flip()
    pygame.quit()


# run the main function only if this module is executed as the main script
# if you import this as a module then nothing is executed
if __name__ == "__main__":
    # call the main function
    main()
