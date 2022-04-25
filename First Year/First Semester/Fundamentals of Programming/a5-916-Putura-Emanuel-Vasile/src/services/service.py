"""
    Service class includes functionalities for implementing program features
"""

from src.domain.entity import Complex
from random import randint
from copy import deepcopy


class ComplexService:
    def __init__(self):
        self.__complex_nos = []
        self.__history = []

    @property
    def complex_nos(self):
        return self.__complex_nos

    @property
    def history(self):
        return self.__history

    def update_history(self):
        self.__history.append(deepcopy(self.__complex_nos))

    def undo_operation(self):
        if not len(self.__history):
            raise ValueError('Cannot undo anymore.')
        self.__complex_nos = deepcopy(self.__history.pop())

    def add_complex_no(self, complex_no):
        """
        Adds a complex number to the list of complex numbers
        :param complex_no: a complex number in string format
        :return: -
        """
        self.update_history()  # update the history list
        complex_no = Complex.from_string(complex_no)
        if not isinstance(complex_no, Complex):
            raise ValueError("Invalid complex number.")
        self.__complex_nos.append(complex_no)

    def filter_complex_nos_by_indices(self, start, end):
        """
        Filters the complex numbers list attribute so that it contains only the numbers between indices start and end
        :param start: an start index
        :param end: an end index
        :return: -
        """
        self.update_history()
        self.__complex_nos = list(filter(lambda cn: self.__complex_nos.index(cn) in range(start, end + 1), self.__complex_nos))

    def find_complex_with_real_part(self, real_part):
        """
        Checks if there is a complex number in the list with a given real part
        :param real_part: a real part
        :return: True if there is such a number, False else
        """
        for cn in self.__complex_nos:
            if cn.real_part == real_part:
                return True
        return False

    def generate_default_complex_nos(self):
        """
        Generates some default complex numbers and appends them to the complex numbers list
        :return: -
        """
        for i in range(10):
            real_part = randint(-9, 9)
            imaginary_part = randint(-9, 9)
            while self.find_complex_with_real_part(real_part):
                real_part = randint(-9, 9)
            self.__complex_nos.append(Complex(real_part, imaginary_part))


