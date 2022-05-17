class Sensor:
    def __init__(self, x, y, energy=0):
        self.__x = x
        self.__y = y
        self.__energy = energy

    @property
    def x(self):
        return self.__x

    @property
    def y(self):
        return self.__y

    @property
    def energy(self):
        return self.__energy

    @energy.setter
    def energy(self, other):
        self.energy = other

    def __eq__(self, other):
        return self.__x == other.x and self.__y == other.y

    def __hash__(self):
        return (self.__x, self.__y).__hash__()
