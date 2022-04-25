"""
Functions that implement program features. They should call each other, or other functions from the domain
"""

import functools
from src.domain.entity import get_apartment, get_type, get_amount, set_amount, create_expense, create_expenses_list, \
    sort_expenses_list


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


def sum_expense_type(expenses_list, expense_type):
    """
    Finds the total amount for the expenses having a certain type
    :param expenses_list: an expenses list
    :param expense_type: an expense type
    :return: the total amount for the expenses having expense_type type
    """
    expense_type_list = list(filter(lambda expense: get_type(expense) == expense_type, expenses_list))
    expense_type_amount_list = list(map(lambda expense: get_amount(expense), expense_type_list))
    return functools.reduce(lambda amount1, amount2: amount1 + amount2, expense_type_amount_list)


def max_amount_apartment(expenses_list, apartment):
    """
    Finds the maximum amount per each expense type for a certain apartment
    :param expenses_list: an expenses list
    :param apartment: an apartment
    :return: the maximum amount per each expense type for an apartment
    """
    apartment_expenses_list = list(filter(lambda expense: get_apartment(expense) == apartment, expenses_list))
    apartment_amount_list = list(map(lambda expense: get_amount(expense), apartment_expenses_list))
    return functools.reduce(lambda amount1, amount2: amount1 if amount1 > amount2 else amount2, apartment_amount_list)


def sort_apartments_by_total_amount(expenses_list):
    """
    Sorts the list of apartments by total amount of expenses
    :param expenses_list: an expenses list
    :return: the sorted list of apartments
    """
    apartments_total_expenses_list = find_all_apartments_expenses(expenses_list)
    apartments_total_expenses_list.sort(key=lambda apartment_expenses: apartment_expenses[1])
    return list(map(lambda apartment_expenses: apartment_expenses[0], apartments_total_expenses_list))


def find_total_amount_of_expenses_for_type(expenses_list, expense_type):
    """
    Finds the total amount of expenses for a certain expense type
    :param expenses_list: an expenses list
    :param expense_type: an expense type
    :return: the total amount of expenses for expense_type type
    """
    expense_type_list = list(filter(lambda expense: get_type(expense) == expense_type, expenses_list))
    if len(expense_type_list) == 0:
        return
    expense_type_amounts = list(map(lambda expense: get_amount(expense), expense_type_list))
    return functools.reduce(lambda amount1, amount2: amount1 + amount2, expense_type_amounts)


def find_total_expenses_per_type(expenses_list):
    """
    Finds the total amount of expenses per type
    :param expenses_list: an expenses list
    :return: a list of tuples of the following form: [(expense_type, total_amount_of_expenses_for_expense_type), ...]
    """
    expense_type = ["water", "heating", "electricity", "gas", "other"]
    expense_type = filter(lambda type: find_total_amount_of_expenses_for_type(expenses_list, type), expense_type)
    return list(map(lambda type: (type, find_total_amount_of_expenses_for_type(expenses_list, type)), expense_type))


def sort_expense_types_by_total_amount(expenses_list):
    """
    Sorts the expense types by the total amount of expenses per type
    :param expenses_list: an expenses list
    :return: the sorted list of expense types. Each element of the list is a tuple of the following form: (expense_type, total_amount_of_expenses_for_expense_type)
    """
    expenses_per_type = find_total_expenses_per_type(expenses_list)
    expenses_per_type.sort(key=lambda expense_per_type: expense_per_type[1])
    return expenses_per_type


def filter_type(expenses_list, type):
    """
    Returns a list that keeps only the expenses with a certain type
    :param expenses_list: an expenses list
    :param type: an expense type
    :return: a list that keeps only the expenses with the given expense type
    """
    return list(filter(lambda expense: get_type(expense) == type, expenses_list))


def filter_value(expenses_list, value):
    """
    Returns a list that keeps only the expenses with the amount smaller than a given value
    :param expenses_list: an expenses list
    :param value: an amount of money
    :return: a list that keeps only the expenses with the amount smaller than value
    """
    return list(filter(lambda expense: get_amount(expense) < value, expenses_list))


def add_expenses_list_to_history(expenses_list, history):
    """
    Adds an expenses list to the history of expenses list
    :param expenses_list: an expenses list
    :param history: the history of expenses lists
    :return: the updated history of expenses lists
    """
    history.append([])
    for expense in expenses_list:
        history[len(history) - 1].append(expense.copy())
    return history


def undo_command(expenses_list, history):
    """
    Undoes a command
    :param expenses_list: an expenses list
    :param history: the history of expenses lists
    :return: -
    """
    expenses_list[:] = history.pop()


def test_init(test_list, history=None):
    # use this function to add the 10 required items
    # use it to set up test data
    if history is None:
        history = []
    test_list.append(create_expense(29, 200, 'heating'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(25, 100, 'water'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(31, 100, 'gas'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(25, 100, 'gas'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(26, 200, 'water'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(27, 300, 'gas'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(28, 100, 'other'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(29, 201, 'other'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(30, 50, 'gas'))
    history[:] = add_expenses_list_to_history(test_list, history)
    test_list.append(create_expense(25, 500, 'electricity'))


def test_functions():
    test_create_expense()
    test_create_expenses_list()
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
    test_sum_expense_type()
    test_max_amount_apartment()
    test_sort_apartments_by_total_amount()
    test_find_total_amount_of_expenses_for_type()
    test_find_total_expenses_per_type()
    test_sort_expense_types_by_total_amount()
    test_filter_type()
    test_filter_value()
    test_add_expenses_list_to_history()
    test_undo_command()


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


def test_sum_expense_type():
    """
    Test function for sum_expense_type() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert sum_expense_type(expenses_list, 'gas') == 550


def test_max_amount_apartment():
    """
    Test function for max_amount_apartment() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert max_amount_apartment(expenses_list, 25) == 500


def test_sort_apartments_by_total_amount():
    """
    Test function for sort_apartments_by_total_amount() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(sort_apartments_by_total_amount(expenses_list)) == 7


def test_find_total_amount_of_expenses_for_type():
    """
    Test function for find_total_amount_of_expenses_for_type() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert find_total_amount_of_expenses_for_type(expenses_list, 'other') == 301


def test_find_total_expenses_per_type():
    """
    Test function for find_total_expenses_per_type() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(find_total_expenses_per_type(expenses_list)) == 5


def test_sort_expense_types_by_total_amount():
    """
    Test function for sort_expense_types_by_total_amount() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(sort_expense_types_by_total_amount(expenses_list)) == 5


def test_filter_type():
    """
    Test function for filter_type() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(filter_type(expenses_list, 'gas')) == 4


def test_filter_value():
    """
    Test function for filter_value() function
    :return: -
    """
    expenses_list = create_expenses_list()
    test_init(expenses_list)
    assert len(filter_value(expenses_list, 300)) == 8


def test_add_expenses_list_to_history():
    """
    Test function for add_expenses_list_to_history() function
    :return: -
    """
    history = [[]]
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(25, 100, 'gas'))
    add_expenses_list_to_history(expenses_list, history)
    assert len(history) == 2


def test_undo_command():
    """
    Test function for undo_command() function
    :return: -
    """
    history = [[]]
    expenses_list = create_expenses_list()
    expenses_list.append(create_expense(25, 100, 'gas'))
    add_expenses_list_to_history(expenses_list, history)
    undo_command(expenses_list, history)
    assert len(history) == 1
