"""
    Entity class should be coded here
"""

import math
import re


class Complex:
    def __init__(self, real_part=0, imaginary_part=0):
        if not self.is_float(str(real_part)) or not self.is_float(str(imaginary_part)):
            raise ValueError('Real part and imaginary part must be integers.')
        self.__real_part = float(real_part)
        self.__imaginary_part = float(imaginary_part)

    @property
    def real_part(self):
        return self.__real_part

    @property
    def imaginary_part(self):
        return self.__imaginary_part

    @real_part.setter
    def real_part(self, value):
        if not self.is_float(str(value)):
            raise ValueError('Real part must be an integer.')
        self.__real_part = value

    @imaginary_part.setter
    def imaginary_part(self, value):
        if not self.is_float(str(value)):
            raise ValueError('Imaginary part must be an integer.')
        self.__imaginary_part = value

    @staticmethod
    def is_integer_str(string_no):
        if string_no[0] in ('+', '-'):
            return string_no[1:].isdigit()
        return string_no.isdigit()

    @staticmethod
    def is_integer_float(float_no):
        int_no = int(float_no)
        if float_no == int_no:
            return True
        return False

    @staticmethod
    def is_float(string_no):
        if Complex.is_integer_str(string_no):
            return True
        return re.search("[+-]?[0-9]+\.[0-9]+", string_no) is not None

    @classmethod
    def from_string(cls, complex_str):
        """
        Creates a complex number from a string (format: 'a + bi')
        :param complex_str: a string representation of a complex number
        :return: a complex number
        """
        split_complex = complex_str.strip().split(' ')
        if len(split_complex) not in [1, 3]:
            raise ValueError("Invalid complex number.")
        if len(split_complex) == 1:
            if split_complex[0].find('i') != -1:
                if split_complex[0] == 'i':
                    split_complex[0] = '1i'
                if split_complex[0] == '-i':
                    split_complex[0] = '-1i'
                return cls(0, split_complex[0].replace('i', ''))
            return cls(split_complex[0])
        split_complex[2] = split_complex[1] + split_complex[2]
        if split_complex[2] == 'i' or split_complex[2] == '+i':
            split_complex[2] = '1i'
        if split_complex[2] == '-i':
            split_complex[2] = '-1i'
        return cls(split_complex[0], split_complex[2].replace('i', ''))

    def add(self, complex_number):
        """
        Adds two complex numbers
        :param complex_number: a complex number
        :return: a complex number representing the result of the addition
        """
        return Complex(self.__real_part + complex_number.real_part, self.__imaginary_part + complex_number.imaginary_part)

    def __str__(self) -> str:
        """
        Returns the string representation of a complex number
        :return: the string representation of a complex number
        """
        if Complex.is_integer_float(self.__real_part):
            self.__real_part = int(self.__real_part)
        if Complex.is_integer_float(self.__imaginary_part):
            self.__imaginary_part = int(self.__imaginary_part)
        if not self.__imaginary_part:
            return str(self.__real_part)
        if not self.__real_part:
            if not self.__imaginary_part == 1 and not self.__imaginary_part == -1:
                return "{}i".format(self.__imaginary_part)
            if self.__imaginary_part > 0:
                return 'i'
            if self.__imaginary_part < 0:
                return '-i'
        if self.__imaginary_part < 0 and self.__imaginary_part != -1:
            return "{} - {}i".format(self.__real_part, -self.__imaginary_part)
        elif self.__imaginary_part < 0:
            return "{} - i".format(self.__real_part)
        if self.__imaginary_part == 1:
            return "{} + i".format(self.__real_part)
        return "{} + {}i".format(self.__real_part, self.__imaginary_part)

    def __eq__(self, other):
        return self.__real_part == other.real_part and self.__imaginary_part == other.imaginary_part

    def __abs__(self):
        return math.sqrt(self.__real_part ** 2 + self.__imaginary_part ** 2)
