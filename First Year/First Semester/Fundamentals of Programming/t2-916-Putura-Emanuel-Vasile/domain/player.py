class Player:
    def __init__(self, id, name, strength):
        self.__id = id
        self.__name = name
        self.__strength = strength

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @property
    def strength(self):
        return self.__strength

    @strength.setter
    def strength(self, other):
        self.__strength = other

    def __str__(self):
        return '{},{},{}'.format(self.__id, self.__name, self.__strength)
