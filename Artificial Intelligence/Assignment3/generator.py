import random
from utils import DEFAULT_SEED


class RandomGenerator:
    def __init__(self, seed=DEFAULT_SEED):
        self.__seed = seed

    @property
    def seed(self):
        return self.__seed

    def randint(self, a, b):
        return random.randint(a, b)
