#
# Write the implementation for A3 in this file
# Problem no.5: Apartment Building Administrator
#

#
# domain section is here (domain = numbers, transactions, expenses, etc.)
# getters / setters
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)


def create_expense(apartment, amount, type):
    """
    Creates an expense
    :param apartment: number of apartment (the apartment that has this expense). Must be a positive integer
    :param amount: expense amount. Must be a positive integer
    :param type: expense type. A string that must be one of the elements of expense_type list (declared below)
    :return: a new expense
    :exception: ValueError if apartment or amount are < 0
    """
    if apartment < 0:
        raise ValueError("Apartment number must be a positive integer.")
    if amount < 0:
        raise ValueError("Amount value must be a positive integer.")
    return {"apartment": apartment, "amount": amount, "type": type}


def get_apartment(expense):
    """
    Gets the number of the apartment that is responsible for the expense
    :param expense: an expense
    :return: the number of the apartment that is responsible for the expense
    """
    return expense["apartment"]


def get_amount(expense):
    """
    Gets the expense amount
    :param expense: an expense
    :return: the expense amount
    """
    return expense["amount"]


def get_type(expense):
    """
    Gets the expense type
    :param expense: an expense
    :return: the expense type
    """
    return expense["type"]


def set_apartment(expense, apartment):
    """
    Sets the number of the apartment that is responsible for the expense
    :param expense: an expense
    :param apartment: the number of the new apartment that is responsible for the expense
    :return: -
    """
    expense["apartment"] = apartment


def set_amount(expense, amount):
    """
    Sets the expense amount
    :param expense: an expense
    :param amount: the new expense amount
    :return: -
    """
    expense["amount"] = amount


def set_type(expense, type):
    """
    Sets the expense type
    :param expense: an expense
    :param type: the new expense type
    :return: -
    """
    expense["type"] = type


def create_expenses_list():
    """
    Creates an empty list of expenses
    :return: an empty list of expenses
    """
    return []


def to_str(expense):
    """
    Gets the string representation of an expense
    :param expense: an expense
    :return: string representation of an expense
    """
    return "Apartment " + str(get_apartment(expense)) + " has a $" + str(
        get_amount(expense)) + " bill for '" + get_type(expense) + "'."


def apartment_to_str(apartment):
    """
    Gets the string representation of an apartment
    :param apartment: an apartment
    :return: the string representation of an apartment
    """
    return "apartment " + str(apartment)


def is_less_than(expense1, expense2):
    """
    Checks if one expense is less than an other expense. The apartment number is first compared, than in case of equality, the expense type is
    compared and, if they are once again equal, the expense amount is compared
    :param expense1: the first expense
    :param expense2: the second expense
    :return: True if expense1 < expense2, False else
    """
    if get_apartment(expense1) < get_apartment(expense2):
        return True
    if get_apartment(expense1) == get_apartment(expense2) and get_type(expense1) < get_type(expense2):
        return True
    if get_type(expense1) == get_type(expense2) and get_amount(expense1) < get_amount(expense2):
        return True
    return False


def is_equal_to(expense1, expense2):
    """
    Checks if two expenses are equal. In order to be equal they must have the same apartment number, the same expense type and the same expense amount
    :param expense1: the first expense
    :param expense2: the second expense
    :return: True if expense1 = expense2, False else
    """
    return get_apartment(expense1) == get_apartment(expense2) and get_type(expense1) == get_type(
        expense2) and get_amount(expense1) == get_amount(expense2)


def is_greater_than(expense1, expense2):
    """
    Checks if one expense is greater than an other expense. This is true if and only if is_equal_to(expense1, expense2) and is_less_than(expense1, expense2)
    both return False
    :param expense1: the first expense
    :param expense2: the second expense
    :return: True if expense1 > expense2, False else
    """
    if is_less_than(expense1, expense2):
        return False
    if is_equal_to(expense1, expense2):
        return False
    return True


def sort_expenses_list(expenses_list):
    """
    Sorts an expenses list
    :param expenses_list: an expenses list
    :return: -
    """
    for i in range(0, len(expenses_list)):
        for j in range(i + 1, len(expenses_list)):
            if is_greater_than(expenses_list[i], expenses_list[j]):
                expenses_list[i], expenses_list[j] = expenses_list[j], expenses_list[i]


# Functionalities section (functions that implement required features)
# No print or input statements in this section
# Specification for all non-trivial functions (trivial usually means a one-liner)
# Each function does one thing only
# Functions communicate using input parameters and their return values


def add_expense(expenses_list, parameters):
    """
    Adds a new expense to the expenses list. If an expense with the same type was already added to the same apartment, than the amount
    of this expense is added to the initial expense amount; else, a new expense is created and added to expenses list
    :param expenses_list: an expenses list
    :param parameters: <add> command parameters: parameters[0] is the apartment, parameters[1] is the expense type and parameters[2] is
        the expense amount
    :return: -
    """
    apartment = int(parameters[0])
    expense_type = parameters[1]
    amount = int(parameters[2])

    # True if we found an already existing expense with the same type and for the same apartment
    found_similar_expense = False

    for expense in expenses_list:
        if get_apartment(expense) == apartment and get_type(expense) == expense_type:
            found_similar_expense = True
            set_amount(expense, get_amount(expense) + amount)
            break

    if not found_similar_expense:
        expense = create_expense(apartment, amount, expense_type)
        expenses_list.append(expense)


def remove_expenses_for_apartment(expenses_list, parameters):
    """
    Removes all expenses for an apartment
    :param expenses_list: an expenses list
    :param parameters: <remove> command parameters (in this case): parameters[0] is the apartment
    :return: -
    """
    apartment = int(parameters[0])
    expenses_list[:] = [expense for expense in expenses_list if not get_apartment(expense) == apartment]


def remove_type_expenses(expenses_list, parameters):
    """
    Removes all expenses with a certain type from all apartments
    :param expenses_list: an expenses list
    :param parameters: <remove> command parameters (in this case): parameters[0] is the expense type
    :return: -
    """
    expense_type = parameters[0]
    expenses_list[:] = [expense for expense in expenses_list if not get_type(expense) == expense_type]


def remove_expenses_for_apartments_between(expenses_list, parameters):
    """
    Removes all expenses for apartments between two given apartments
    :param expenses_list: an expenses list
    :param parameters: <remove> command parameters (in this case): parameters[0] is the first apartment, parameters[2] is the second apartment and
        parameters[1] is the string 'to'
    :return: -
    """
    apartment1 = int(parameters[0])
    apartment2 = int(parameters[2])
    expenses_list[:] = [expense for expense in expenses_list if
                        not get_apartment(expense) in range(apartment1, apartment2 + 1)]


def replace_expense_amount(expenses_list, parameters):
    """
    Replaces the amount of the expense with a certain type for a certain apartment with a new sum
    :param expenses_list: an expenses list
    :param parameters: <replace> command parameters: parameters[0] is the apartment, parameters[1] is the expense type, parameters[3] is the expense
        amount and parameters[2] is the string 'with'
    :return: -
    """
    apartment = int(parameters[0])
    expense_type = parameters[1]
    amount = int(parameters[3])
    for expense in expenses_list:
        if get_apartment(expense) == apartment and get_type(expense) == expense_type:
            set_amount(expense, amount)


def find_apartments_list(expenses_list):
    """
    Finds all the distinct apartments in an expenses list
    :param expenses_list: an expenses list
    :return: the list of all the distinct apartments in an expenses list
    """
    apartments_list = []
    for expense in expenses_list:
        if get_apartment(expense) not in apartments_list:
            apartments_list.append(get_apartment(expense))
    return apartments_list


def find_all_apartments_expenses(expenses_list):
    """
    Finds the total amount of expenses for each distinct apartment in an expenses list
    :param expenses_list: an expenses list
    :return: a list containing the total amount of expenses for each distinct apartment in an expenses list. Each list element is a tuple with the apartment
        as the first value and with the total amount of expenses for that apartment as the second value
    """
    apartments_list = find_apartments_list(expenses_list)

    for apartment in apartments_list:
        apartment_expense = 0
        for expense in expenses_list:
            if get_apartment(expense) == apartment:
                apartment_expense += get_amount(expense)
        apartments_list[apartments_list.index(apartment)] = (apartment, apartment_expense)
    return apartments_list


def find_all_apartments_with_total_expenses_equal_to(expenses_list, sum):
    """
    Finds all the apartments from an expenses list having total expenses equal to a given sum of money
    :param expenses_list: an expenses list
    :param sum: a sum of money
    :return: the list of all the apartments from expenses_list having total expenses equal to sum
    """
    apartments_expenses_list = find_all_apartments_expenses(expenses_list)
    apartments_list = []
    for apartment in apartments_expenses_list:
        if apartment[1] == sum:
            apartments_list.append(apartment[0])
    return apartments_list


def find_all_apartments_with_total_expenses_less_than(expenses_list, sum):
    """
    Finds all the apartments from an expenses list having total expenses less than a given sum of money
    :param expenses_list: an expenses list
    :param sum: a sum of money
    :return: the list of all the apartments from expenses_list having total expenses less than sum
    """
    apartments_expenses_list = find_all_apartments_expenses(expenses_list)
    apartments_list = []
    for apartment in apartments_expenses_list:
        if apartment[1] < sum:
            apartments_list.append(apartment[0])
    return apartments_list


def find_all_apartments_with_total_expenses_greater_than(expenses_list, sum):
    """
    Finds all the apartments from an expenses list having total expenses greater than a given sum of money
    :param expenses_list: an expenses list
    :param sum: a sum of money
    :return: the list of all the apartments from expenses_list having total expenses greater than sum
    """
    apartments_expenses_list = find_all_apartments_expenses(expenses_list)
    apartments_list = []
    for apartment in apartments_expenses_list:
        if apartment[1] > sum:
            apartments_list.append(apartment[0])
    return apartments_list


def find_all_apartment_with_certain_expense(expenses_list, symbol, sum):
    """
    Being given a symbol and a sum of money, finds all the apartments from an expenses list with a certain expense amount property (</> than sum or equal to sum)
    :param expenses_list: an expenses list
    :param symbol: a symbol. Must be '<', '>' or '='
    :param sum: a sum of money
    :return: Returns a list containing all the apartments from expenses_list with a certain expense amount property (</> than sum or equal to sum)
    """
    apartments = []
    if symbol == '=':
        apartments = find_all_apartments_with_total_expenses_equal_to(expenses_list, sum)
    elif symbol == '<':
        apartments = find_all_apartments_with_total_expenses_less_than(expenses_list, sum)
    elif symbol == '>':
        apartments = find_all_apartments_with_total_expenses_greater_than(expenses_list, sum)
    return apartments


# UI section
# (all functions that have input or print statements, or that CALL functions with print / input are  here).
# Ideally, this section should not contain any calculations relevant to program functionalities


def add_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <add> command. When called, it finally adds a new expense to the expenses list (after calling another non-UI function)
    :param expenses_list: an expenses list
    :param command_parameters: <add> command parameters: parameters[0] is the apartment number, parameters[1] is the expense type and parameters[2] is the
        expense amount
    :return: -
    :exception: raises ValueError if expense type is not en element of expense_type list or if apartment number/expense amount are not positive integers.
        Also raises ValueError if <add> command gets more or less parameters than 3
    """
    parameters = command_parameters.split(' ')
    expense_type = ["water", "heating", "electricity", "gas", "other"]  # the possible types for an expense

    if len(parameters) != 3:
        raise ValueError("Invalid parameters for command 'add'.")
    if not parameters[0].isdigit():
        raise ValueError("Apartment number must be a positive integer.")
    if parameters[1] not in expense_type:
        raise ValueError("Invalid expense type.")
    if not parameters[2].isdigit():
        raise ValueError("Amount value must be a positive integer.")

    add_expense(expenses_list, parameters)


def remove_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <remove> command
    :param expenses_list: an expenses list
    :param command_parameters: <remove> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    parameters = command_parameters.split(' ')
    if len(parameters) == 1 and parameters[0].isdigit():
        remove_expenses_for_apartment(expenses_list, parameters)
    elif len(parameters) == 1:
        remove_type_expenses(expenses_list, parameters)
    elif len(parameters) == 3 and 'to' in parameters:
        if not parameters[0].isdigit() or not parameters[2].isdigit():
            raise ValueError("Apartment number must be a positive integer.")
        remove_expenses_for_apartments_between(expenses_list, parameters)
    else:
        raise ValueError("Invalid parameters for command 'remove'.")


def replace_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <replace> command
    :param expenses_list: an expenses list
    :param command_parameters: <replace> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    parameters = command_parameters.split(' ')
    expense_type = ["water", "heating", "electricity", "gas", "other"]

    if len(parameters) != 4 or 'with' not in parameters or parameters[2] != 'with':
        raise ValueError("Invalid parameters for command 'replace'.")
    if not parameters[0].isdigit():
        raise ValueError("Apartment number must be a positive integer.")
    if parameters[1] not in expense_type:
        raise ValueError("Invalid expense type.")
    if not parameters[3].isdigit():
        raise ValueError("Amount value must be a positive integer.")

    replace_expense_amount(expenses_list, parameters)


def display_all_expenses_ui(expenses_list):
    """
    Displays all the string representations of the expenses in a given expenses list
    :param expenses_list: an expenses list
    :return: -
    """
    for expense in expenses_list:
        print(to_str(expense))


def display_all_expenses_for_apartment(expenses_list, parameters):
    """
    Displays all the string representations of the expenses of an apartment from a given expenses list
    :param expenses_list: an expenses list
    :param parameters: <list> command parameters
    :return: -
    """
    apartment = int(parameters[0])
    for expense in expenses_list:
        if get_apartment(expense) == apartment:
            print(to_str(expense))


def display_all_apartments_with_certain_expenses(expenses_list, parameters):
    """
    Displays all the strings representations of the apartments from a given expenses list, having a certain expense property
    :param expenses_list: an expenses list
    :param parameters: <list> command parameters
    :return:
    """
    symbol = parameters[0]
    sum = int(parameters[1])
    apartments = find_all_apartment_with_certain_expense(expenses_list, symbol, sum)

    for apartment in apartments:
        print(apartment_to_str(apartment))


def list_command_ui(expenses_list, command_parameters):
    """
    Checks user input for <list> command and calls a matching function
    :param expenses_list: an expenses list
    :param command_parameters: <list> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    sort_expenses_list(expenses_list)
    parameters = []
    if len(command_parameters) > 0:
        parameters = command_parameters.split(' ')

    if len(parameters) > 2 or (len(parameters) == 2 and not parameters[0] in ('<', '>', '=')):
        raise ValueError("Invalid parameters for command 'list'.")
    if len(parameters) == 1 and not parameters[0].isdigit():
        raise ValueError("Apartment number must be a positive integer.")
    if len(parameters) == 2 and not parameters[1].isdigit():
        raise ValueError("Amount value must be a positive integer.")

    if len(parameters) == 0:
        display_all_expenses_ui(expenses_list)
    elif len(parameters) == 1:
        display_all_expenses_for_apartment(expenses_list, parameters)
    elif len(parameters) == 2:
        display_all_apartments_with_certain_expenses(expenses_list, parameters)


def split_command(command):
    """
    Splits a user command
    :param command: a user command
    :return: a list containing the user command and its parameters
    """
    tokens = command.split(' ', 1)
    return tokens[0].strip().lower(), tokens[1].strip() if len(tokens) == 2 else ''


def start_command_ui():
    """
    Starts the console-based user interface
    :return: -
    """
    expenses_list = create_expenses_list()
    commands = {"add": add_command_ui, "remove": remove_command_ui, "replace": replace_command_ui,
                "list": list_command_ui}
    done = False
    test_init(expenses_list)

    while not done:
        try:
            command = input('command >').strip()
            command_word, command_parameters = split_command(command)

            if command_word in commands:
                commands[command_word](expenses_list, command_parameters)
            elif "help" == command_word:
                print("List of commands:\n(A) Add new transaction\n1. add <apartment> <type> <amount>\n(B) Modify expenses\n2. remove <apartment>")
                print("3. remove <start apartment> to <end apartment>\n4. remove <type>\n5. replace <apartment> <type> with <amount>\n(C) Display expenses having different properties")
                print("6. list\n7. list <apartment>\n8. list [ < | = | > ] <amount>\n")
            elif 'exit' == command_word:
                done = True
            else:
                print("'" + command_word + "'", "is not recognized as a valid command.")
        except ValueError as value_error:
            print(str(value_error))


# Test functions go here
#
# Test functions:
#   - no print / input
#   - great friends with assert

def test_init(test_list):
    # use this function to add the 10 required items
    # use it to set up test data
    test_list.append(create_expense(29, 200, 'heating'))
    test_list.append(create_expense(25, 100, 'water'))
    test_list.append(create_expense(31, 100, 'gas'))
    test_list.append(create_expense(25, 100, 'gas'))
    test_list.append(create_expense(26, 200, 'water'))
    test_list.append(create_expense(27, 300, 'gas'))
    test_list.append(create_expense(28, 100, 'other'))
    test_list.append(create_expense(29, 201, 'other'))
    test_list.append(create_expense(30, 50, 'gas'))
    test_list.append(create_expense(25, 500, 'electricity'))


def test_functions():
    test_create_expense()
    test_create_expenses_list()
    test_is_less_than()
    test_is_equal_to()
    test_is_greater_than()
    test_sort_expenses_list()
    test_add_expense()
    test_remove_expenses_for_apartment()
    test_remove_type_expenses()
    test_remove_expenses_for_apartments_between()
    test_replace_expense_amount()
    test_find_apartments_list()
    test_find_all_apartments_expenses()
    test_find_all_apartments_with_total_expenses_equal_to()
    test_find_all_apartments_with_total_expenses_less_than()
    test_find_all_apartments_with_total_expenses_greater_than()


def test_create_expense():
    """
    Test function for create_expense() function
    :return: -
    """
    assert get_apartment(create_expense(25, 100, "gas")) == 25

    try:
        create_expense(-25, 100, 'other')
        assert False
    except ValueError:
        assert True


def test_create_expenses_list():
    """
    Test function for create_expenses_list() function
    :return: -
    """
    expenses_list = create_expenses_list()
    assert len(expenses_list) == 0


def test_is_less_than():
    """
    Test function for is_less_than() function
    :return: -
    """
    assert is_less_than(create_expense(25, 100, 'gas'), create_expense(25, 101, 'other'))


def test_is_equal_to():
    """
    Test function for is_equal_to() function
    :return: -
    """
    assert is_equal_to(create_expense(25, 100, 'heating'), create_expense(25, 100, 'heating'))


def test_is_greater_than():
    """
    Test function for is_greater_than() function
    :return: -
    """
    assert is_greater_than(create_expense(25, 101, 'other'), create_expense(25, 100, 'gas'))


def test_sort_expenses_list():
    """
    Test function for sort_expenses_list() function
    :return: -
    """
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(29, 200, 'heating'))
    expenses_list.append(create_expense(25, 100, 'water'))

    sort_expenses_list(expenses_list)
    for index in range(1, len(expenses_list)):
        assert is_less_than(expenses_list[index - 1], expenses_list[index])


def test_add_expense():
    """
    Test function for add_expense() function
    :return: -
    """
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(29, 200, 'heating'))
    expenses_list.append(create_expense(25, 100, 'water'))
    add_expense(expenses_list, [25, 'gas', 100])
    assert len(expenses_list) == 3
    assert expenses_list[2] == create_expense(25, 100, 'gas')


def test_remove_expenses_for_apartment():
    """
    Test function for remove_expenses_for_apartment() function
    :return: -
    """
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(29, 200, 'heating'))
    expenses_list.append(create_expense(25, 100, 'water'))
    remove_expenses_for_apartment(expenses_list, [29])
    assert len(expenses_list) == 1
    assert expenses_list[0] == create_expense(25, 100, 'water')


def test_remove_type_expenses():
    """
    Test function for remove_type_expenses() function
    :return: -
    """
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(29, 200, 'heating'))
    expenses_list.append(create_expense(25, 100, 'water'))
    expenses_list.append(create_expense(29, 100, 'water'))
    remove_type_expenses(expenses_list, ['water'])
    assert len(expenses_list) == 1
    assert expenses_list[0] == create_expense(29, 200, 'heating')


def test_remove_expenses_for_apartments_between():
    """
    Test function for remove_expenses_for_apartments_between() function
    :return: -
    """
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(29, 200, 'heating'))
    expenses_list.append(create_expense(25, 100, 'water'))
    expenses_list.append(create_expense(26, 100, 'water'))
    remove_expenses_for_apartments_between(expenses_list, ['25', 'to', '26'])
    assert len(expenses_list) == 1
    assert expenses_list[0] == create_expense(29, 200, 'heating')


def test_replace_expense_amount():
    """
    Test function for replace_expense_amount() function
    :return: -
    """
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(29, 200, 'heating'))
    expenses_list.append(create_expense(25, 100, 'water'))
    expenses_list.append(create_expense(26, 100, 'water'))
    replace_expense_amount(expenses_list, [25, 'water', 'with', 2000])
    assert expenses_list[1] == create_expense(25, 2000, 'water')


def test_find_apartments_list():
    """
    Test function for find_apartments_list() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(find_apartments_list(expenses_list)) == 7


def test_find_all_apartments_expenses():
    """
    Test function for find_all_apartments_expenses() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    sort_expenses_list(expenses_list)
    assert find_all_apartments_expenses(expenses_list)[0][0] == 25 and find_all_apartments_expenses(expenses_list)[0][
        1] == 700


def test_find_all_apartments_with_total_expenses_equal_to():
    """
    Test function for find_all_apartments_with_total_expenses_equal_to() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(find_all_apartments_with_total_expenses_equal_to(expenses_list, 700)) == 1 and \
           find_all_apartments_with_total_expenses_equal_to(expenses_list, 700)[0] == 25


def test_find_all_apartments_with_total_expenses_less_than():
    """
    Test function for find_all_apartments_with_total_expenses_less_than() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(find_all_apartments_with_total_expenses_less_than(expenses_list, 100)) == 1


def test_find_all_apartments_with_total_expenses_greater_than():
    """
    Test function for find_all_apartments_with_total_expenses_greater_than() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(find_all_apartments_with_total_expenses_greater_than(expenses_list, 50)) == 6


# Main function goes here
# this is where start_command_ui() is called
if __name__ == "__main__":
    test_functions()
    start_command_ui()
