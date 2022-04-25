#
# Write the implementation for A2 in this file
#


# UI section
# (write all functions that have input or print statements here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def ui_read_complex_number():
    """
    Reads a complex number as input from the user and then parses it and returns it
    :return: the complex number
    """
    line = input("z = ")
    complex_number = parse_complex_number(line)
    return create_complex_number(complex_number[0], complex_number[1])


def ui_read_complex_numbers_list(list):
    """
    Reads complex numbers from console until the user inputs 'end'
    :param list: a list of complex numbers
    :return: returns once the user inputs 'end'
    """
    while True:
        complex_number = ui_read_complex_number()
        add_list_element(list, complex_number)  # list.append(complex_number)
        value = input("\nType 'end' if you want to stop reading complex numbers: ")
        if value == "end":
            return


def ui_display_complex_numbers_list(list):
    """
    Displays the entire list of complex numbers
    :param list: a list of complex numbers
    :return: -
    """
    for complex_number in list:
        print(to_str(complex_number))


def ui_display_sequence_p2(list):
    """
    Displays the longest sequence that observes property2:
        2. Contains at most 3 distinct values.
    :param list: a list of complex numbers
    :return: -
    """
    # displays the elements of the list, without the last one
    sequence = find_sequence_p2_efficient_solution(list)
    for complex_number in sequence[:-1]:
        print(to_str(complex_number), end=', ')  # after each element, but for the last one, print a ','
    print(to_str(sequence[-1]))


def ui_display_sequence_p12(list):
    """
    Displays the longest sequence that observes property12:
        12. Both real and imaginary parts can be written using the same base 10 digits (e.g. 1+3i, 31i, 33+i, 11-313i)
    :param list: a list of complex numbers
    :return: -
    """
    # displays the elements of the list, without the last one
    sequence = find_sequence_p12(list)
    for complex_number in sequence[:-1]:
        print(to_str(complex_number), end=', ')  # after each element, but for the last one, print a ','
    print(to_str(sequence[-1]))


def run():
    """
    Handles the main menu
    :return: returns once the user inputs 'x'
    """
    list = create_complex_numbers_list()
    add_default_complex_numbers_list(list)
    while True:
        print_menu()
        option = input("Enter option: ")

        if option == "r":
            ui_read_complex_numbers_list(list)
        elif option == "d":
            ui_display_complex_numbers_list(list)
        elif option == "a":
            ui_display_sequence_p2(list)
        elif option == "b":
            ui_display_sequence_p12(list)
        elif option == "x":
            return
        else:
            print("Invalid command!")


def print_menu():
    """
    Prints the menu
    """
    print("\nr - read a list of complex numbers (in z = a + bi form, where a, b are real numbers). ")
    print("d - display the entire list of numbers")
    print("a - display the longest sequence that observes property 2")
    print("b - display the longest sequence that observes property 12")
    print("x - exit the application\n")
    print("Properties:\n2. Contains at most 3 distinct values.")
    print("12. Both real and imaginary parts can be written using the same base 10 digits (e.g. 1+3i, 31i, 33+i, "
          "11-313i)")


# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!


def are_equal(complex_number1, complex_number2):
    """
    Checks if two given complex numbers are equal or not
    :param complex_number1: the first complex number
    :param complex_number2: the second complex number
    :return: True if the numbers are equal, False otherwise
    """
    if get_real_part(complex_number1) != get_real_part(complex_number2):
        return False
    if get_imag_part(complex_number1) != get_imag_part(complex_number2):
        return False
    return True


def transform_digits_list(digits_list, number):
    """
    Transforms the digits list: digits_list[i] = 1 <=>
            <=> i is a base10 digit in the real or in the imaginary part of number, 0 otherwise
    Number must be an integer! If it is not, the function tries to convert it to int
    :param digits_list:
    :param number:
    """
    number = int(number)
    # number must be >= 0
    if number < 0:
        number = -number
    while number != 0:
        digits_list[number % 10] = 1
        number //= 10


def get_base10_digits(complex_number):
    """
    Gets a list with possible values 1 or 0: l[i] = 1 <=>
            <=> i is a base10 digit in the real or in the imaginary part of complex_number, 0 otherwise
    :param complex_number: a complex number
    :return: the digits list
    """
    digits_list = [0] * 10
    transform_digits_list(digits_list, get_real_part(complex_number))
    transform_digits_list(digits_list, get_imag_part(complex_number))

    return digits_list


def find_list_element(list, element):
    """
    Finds an element in a list and returns its position index (if the element is in the list)
    :param list: a list
    :param element: a possible element of the list
    :return: the position index of element if it is in list, -1 otherwise
    """
    index = 0
    for e in list:
        if e == element:
            return index
        index += 1
    return -1


def find_list_min_index(list):
    """
    Finds the minimum of a list and its index
    :param list: a list
    :return: the position index of the minimum of the list
    """
    min_index = index = 0
    min = list[0]
    for element in list:
        if element < min:
            min = element
            min_index = index
        index += 1
    return min_index


def are_lists_equal(list1, list2):
    """
    Checks if two given lists are equal or not
    :param list1: the first list
    :param list2: the second list
    :return: True if the lists are equal, False otherwise
    """
    if len(list1) != len(list2):  # if the lists are equal, they must have the same length
        return False
    for i in range(len(list1)):
        if list1[i] != list2[i]:
            return False
    return True


def same_base10_digits(complex_number1, complex_number2):
    """
    Checks if both real and imaginary parts of two complex numbers can be written using the same base 10 digits
    :param complex_number1: the first complex number
    :param complex_number2: the second complex number
    :return: True if both real and imaginary parts of two complex numbers can be written using the same base 10 digits,
             False otherwise
    """
    digits_list1 = get_base10_digits(complex_number1)
    digits_list2 = get_base10_digits(complex_number2)
    return are_lists_equal(digits_list1, digits_list2)


def is_integer(float_number):
    """
    Checks if a number is an integer or not
    :param float_number: the float number to be checked
    :return: True if float_number is an integer and False otherwise
    """
    int_number = int(float_number)
    if float_number == int_number:
        return True
    return False


def create_complex_number(real_part, imaginary_part):
    """
    Creates a new complex number with given real part and imaginary part
    :param real_part: the real part of the complex number
    :param imaginary_part: the imaginary part of the complex number
    :return: a new complex number
    """
    if is_integer(real_part):
        real_part = int(real_part)
    if is_integer(imaginary_part):
        imaginary_part = int(imaginary_part)

    return {"real": real_part, "imag": imaginary_part}


def get_real_part(complex_number):
    """
    Gets the real part of a complex number
    :param complex_number: a complex number
    :return: the real part of a complex number
    """
    return complex_number["real"]


def get_imag_part(complex_number):
    """
    Gets the imaginary part of a complex number
    :param complex_number: a complex number
    :return: the imaginary part of a complex number
    """
    return complex_number["imag"]


def set_real_part(complex_number, real_part):
    """
    Sets the real part of a complex number
    :param complex_number: a complex number
    :param real_part: the new real part of complex_number
    """
    complex_number["real"] = real_part


def set_imag_part(complex_number, imag_part):
    """
    Sets the imaginary part of a complex number
    :param complex_number: a complex number
    :param imag_part: the new imaginary part of complex_number
    """
    complex_number["imag"] = imag_part


def to_str(complex_number):
    """
    Returns the string representation of a complex number
    :param complex_number: a complex number
    :return: the string representation of complex_number
    """
    real_part = get_real_part(complex_number)
    imag_part = get_imag_part(complex_number)
    if real_part != 0 and imag_part != 0:
        if imag_part < 0:
            im_sign = " - "
            imag_part = -imag_part
        else:
            im_sign = " + "
        if imag_part == 1:  # so that a complex number with its imaginary part 1 or -1 is not represented as a +(-) 1i
            return "z = " + str(real_part) + im_sign + "i"
        return "z = " + str(real_part) + im_sign + str(imag_part) + "i"
    if real_part != 0:
        return "z = " + str(real_part)
    if imag_part == 1:
        return "z = i"
    if imag_part == -1:
        return "z = -i"
    return "z = " + str(imag_part) + "i"


def add_list_element(list, element):
    """
    Adds an element to a list
    :param list: a list
    :param element: an element
    :return: -
    """
    list.append(element)


def find_sequence_p2(cn_list):
    """
    Finds the longest sequence that observes property2:
        2. Contains at most 3 distinct values.
    :param cn_list: a list of complex numbers
    :return: a list containing the found sequence
    """
    # max_length - the length of the found sequence
    # length - length of a possible sequence
    # start_index, final_index - the start and the final index of the found sequence
    max_length = start_index = 0
    for index in range(len(cn_list)):  # for each complex number in the list
        seq_list = []  # the numbers in a possible sequence that respects P2 (only 3 different numbers)
        length = 0
        for i in range(index, len(cn_list)):
            length += 1
            # if cn_list[i] is an element different from the ones in seq_list
            if not (cn_list[i] in seq_list):
                seq_list.append(cn_list[i])
                # seq_list contains all the different numbers of a sequence respecting P2,
                # so it has at most 3 elements
                if len(seq_list) > 3:
                    length -= 1
                    if max_length < length:
                        start_index = index
                        max_length = length
                    break
    final_index = start_index + max_length - 1
    return cn_list[start_index:final_index + 1]


def find_sequence_p2_efficient_solution(cn_list):
    """
    Finds the longest sequence that observes property12:
        12. Both real and imaginary parts can be written using the same base 10 digits (e.g. 1+3i, 31i, 33+i, 11-313i)
    This function does the same as find_sequence_p12() function, but it does it in a time complexity of O(n).
    :param cn_list: a list of complex numbers
    :return: a list containing the found sequence
    """
    sequence_cn = []  # this is a 3 elements list that contains the elements from a possible list with the given property P2
    sequence_last_cn_app = []  # sequence_last_cn_ap[i] = p <=> p is the last apparition of the element sequence_cn[i] in cn_list
    length = index = final_index = max_length = 0
    for cn in cn_list:
        if len(sequence_cn) < 3:  # the case when we have not yet found 3 distinct elements in the list is a particular one
            length += 1
            if cn in sequence_cn:
                sequence_last_cn_app[find_list_element(sequence_cn, cn)] = index  # Note that the two local lists used in this function
                # have at most 3 elements, so the time complexity remains O(n)
            else:
                sequence_cn.append(cn)
                sequence_last_cn_app.append(index)
        else:
            if cn in sequence_cn:
                sequence_last_cn_app[find_list_element(sequence_cn, cn)] = index
                length += 1
            else:
                m_index = find_list_min_index(sequence_last_cn_app)
                min_index = sequence_last_cn_app[m_index]
                sequence_cn[m_index] = cn
                sequence_last_cn_app[m_index] = index
                length = index - min_index

        if length > max_length:
            max_length = length
            final_index = index
        index += 1

    start_index = final_index - max_length + 1
    return cn_list[start_index:final_index + 1]


def find_sequence_p12(cn_list):
    """
    Finds the longest sequence that observes property12:
        12. Both real and imaginary parts can be written using the same base 10 digits (e.g. 1+3i, 31i, 33+i, 11-313i)
    :param cn_list: a list of complex numbers
    :return: a list containing the found sequence
    """
    # index - the index in the list
    # max_length - the length of the found sequence
    # length - length of a possible sequence
    # start_index, final_index - the start and the final index of the found sequence
    index = length = max_length = final_index = 0
    prev_cn = cn_list[0]  # previous complex number in the list
    for cn in cn_list[1:]:  # we start from the second element of the list
        if length > max_length:
            max_length = length
            final_index = index
        if same_base10_digits(prev_cn, cn):
            length += 1
        else:
            length = 1
        prev_cn = cn
        index += 1
    start_index = final_index - max_length + 1
    return cn_list[start_index:final_index + 1]


def parse_complex_number(line):
    """
    Parses a line read from the console, representing a complex number
    :param line: a line read from the console, representing a complex number
    :return: a tuple containing the real and the imaginary part of the complex number
    """
    line = line.strip()
    elements = line.split()
    real_part = imaginary_part = 0
    sign = None

    if len(elements) > 1:  # checks if the real and the imaginary part are different from zero (both of them)
        real_part = float(elements[0])
        sign = elements[1]  # a +/- bi => sign = '+'/'-'
        if elements[2] == "i":
            elements[2] = "1i"
        imaginary_part = float(elements[2][:-1])
    elif len(elements) == 1:
        if elements[0].find("i") != -1:
            if elements[0] == "i":
                elements[0] = "1i"
            elif elements[0] == "-i":
                elements[0] = "-1i"
            imaginary_part = float(elements[0][:-1])
        else:
            real_part = float(elements[0])

    if sign == '-':
        imaginary_part = -imaginary_part
    return real_part, imaginary_part


def add_default_complex_numbers_list(list):
    """
    Adds some default values to the complex numbers list
    :param list: a list of complex numbers
    :return: -
    """
    add_list_element(list, create_complex_number(1, 2))
    add_list_element(list, create_complex_number(3, 4.8))
    add_list_element(list, create_complex_number(1, -2))
    add_list_element(list, create_complex_number(-3, 0))
    add_list_element(list, create_complex_number(1, -2))
    add_list_element(list, create_complex_number(3, 4.8))
    add_list_element(list, create_complex_number(1, 3))
    add_list_element(list, create_complex_number(0, 31))
    add_list_element(list, create_complex_number(113, 0))
    add_list_element(list, create_complex_number(1, -2))


def create_complex_numbers_list():
    """
    Creates a list of complex numbers
    :return: a new list of complex numbers
    """
    return []


# run()


if __name__ == "__main__":
    run()
