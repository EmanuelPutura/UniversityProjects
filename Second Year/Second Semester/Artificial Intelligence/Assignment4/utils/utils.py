# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
YELLOW = (253, 218, 13)

# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

# define indexes variations
VARIATIONS = [[-1, 0], [1, 0], [0, 1], [0, -1]]

# define mapsize
MAP_LENGTH = 20

# define default fill factor
FILL_FACTOR = 0.2

# algorithm default setup parameters
DRONE_START = (0, 0)
DRONE_ENERGY = 10
SENSORS = [(1, 2), (6, 7), (15, 11), (10, 10), (19, 19)]

EPOCHS_NUMBER = 100
ANTS_NUMBER = 10
ALPHA = 1.9
BETA = 0.9
BEST_CHOICE_PROBABILITY = 1
EVAPORATION_COEFFICIENT = 0.05
