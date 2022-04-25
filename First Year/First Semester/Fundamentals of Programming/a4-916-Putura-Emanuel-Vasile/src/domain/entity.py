"""
Domain file includes code for entity management
entity = number, transaction, expense etc.
"""


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


def sort_expenses_list(expenses_list):
    """
    Sorts an expenses list
    :param expenses_list: an expenses list
    :return: -
    """
    expenses_list.sort(key=lambda expense: str(get_apartment(expense)) + str(get_amount(expense)) + get_type(expense))
