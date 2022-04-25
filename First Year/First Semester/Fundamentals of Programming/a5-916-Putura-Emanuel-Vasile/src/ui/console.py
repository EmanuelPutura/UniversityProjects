"""
    UI class.

    Calls between program modules
    ui -> service -> entity
    ui -> entity
"""

from src.services.service import ComplexService


class Console:
    def __init__(self, complex_service=None):
        if complex_service is not None:
            if not isinstance(complex_service, ComplexService):
                raise ValueError("Invalid complex service.")
            self.__complex_service = complex_service
        else:
            self.__complex_service = ComplexService()

    @staticmethod
    def print_menu():
        print("Complex Numbers List Manager")
        print("1 - add a complex number number")
        print("2 - display the list of complex numbers")
        print("3 - filter the list so that it contains only the numbers between certain indices")
        print("4 - undo the last operation")
        print("x - exit\n")

    @staticmethod
    def get_option():
        option = input("option> ").strip()
        if option not in ('1', '2', '3', '4', 'x'):
            raise ValueError("Invalid option.")
        return option

    def add_complex_number(self):
        complex_no = input("Input a complex number in format 'a + bi': ")
        self.__complex_service.add_complex_no(complex_no)

    def display_complex_nos_list(self):
        for complex_no in self.__complex_service.complex_nos:
            print(complex_no)

    def filter_list_by_indices(self):
        indices = input("Please input two indices in format 'start, end': ").strip().split(',')
        indices[0] = indices[0].strip()
        indices[1] = indices[1].strip()
        if not indices[0].isdigit() or not indices[1].isdigit():
            raise ValueError("Invalid indices.")
        self.__complex_service.filter_complex_nos_by_indices(int(indices[0]), int(indices[1]))

    def undo_operation(self):
        self.__complex_service.undo_operation()

    def generate_default_numbers(self):
        self.__complex_service.generate_default_complex_nos()

    def run(self):
        options = {'1': self.add_complex_number, '2': self.display_complex_nos_list, '3': self.filter_list_by_indices,
                   '4': self.undo_operation}

        self.generate_default_numbers()
        while True:
            try:
                Console.print_menu()
                option = self.get_option()
                if option == 'x':
                    break
                options[option]()
            except ValueError as value_error:
                print(str(value_error) + '\n')
