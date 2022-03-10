class Constants:
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
    FILL_FACTOR = 0.2

    # board dimensions
    BOARD_DIM = 20
    CELL_SIZE = 20

    # define indexes variations
    VARIATIONS = [[0, -1], [1, 0], [0, 1], [-1, 0]]
    DIRECTION_TO_VARIATION = {(-1, 0): LEFT, (1, 0): RIGHT, (0, -1): UP, (0, 1): DOWN}
