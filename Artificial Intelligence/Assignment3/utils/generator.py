import random
from utils.utils import DEFAULT_SEED


class RandomGenerator:
    def __init__(self, seed=DEFAULT_SEED):
        self.__seed = seed

    @property
    def seed(self):
        return self.__seed

    @seed.setter
    def seed(self, other):
        self.__seed = other

    def randint(self, a, b):
        return random.randint(a, b)
