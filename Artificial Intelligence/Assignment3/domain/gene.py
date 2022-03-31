"""
    Chromosome representation
    - each chromosome consists of a vector of directions, represented as indices in the VARIATIONS vector defined in utils
    - hence, each gene is represented as a direction (i.e., an integer in the interval [0, 3])
"""


class Gene:
    def __init__(self, generator):
        # random initialise the gene according to the representation
        self.__generator = generator
        self.__value = generator.randint(0, 3)

    @property
    def value(self):
        return self.__value

    @value.setter
    def value(self, other):
        self.__value = other

    def __deepcopy__(self):
        newGene = Gene(self.__generator)
        newGene.value = self.__value
        return newGene

    def __eq__(self, other):
        return self.__value == other.value
