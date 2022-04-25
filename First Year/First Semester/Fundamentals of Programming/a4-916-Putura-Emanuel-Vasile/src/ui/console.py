"""
This is the user interface module. These functions call functions from the domain and functions module.
"""

from src.domain.entity import to_str, apartment_to_str, sort_expenses_list, create_expenses_list
from src.functions.functions import add_expense, remove_expenses_for_apartment, remove_type_expenses, remove_expenses_for_apartments_between,\
    replace_expense_amount, get_apartment, find_all_apartment_with_certain_expense, sum_expense_type, max_amount_apartment, sort_apartments_by_total_amount,\
    sort_expense_types_by_total_amount, filter_type, filter_value, add_expenses_list_to_history, test_init, undo_command


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
    if not len(expenses_list):
        print("There are no expenses.")


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


def sum_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <sum> command
    :param expenses_list: an expenses list
    :param command_parameters: <sum> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    expense_type = ["water", "heating", "electricity", "gas", "other"]
    parameters = command_parameters.split(' ')
    if parameters == ['']:
        parameters = []

    if len(parameters) != 1 or parameters[0] not in expense_type:
        raise ValueError("Invalid parameters from command 'sum'.")
    display_total_amount_for_expenses_with(expenses_list, parameters[0])


def display_total_amount_for_expenses_with(expenses_list, expense_type):
    """
    Displays the string representation of the total amount for the expenses having a certain type
    :param expenses_list: an expenses list
    :param expense_type: an expense type
    :return: -
    """
    sum = sum_expense_type(expenses_list, expense_type)
    print(f"The total amount for the expenses having type '{expense_type}' is ${sum}.")


def max_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <max> command
    :param expenses_list: an expenses list
    :param command_parameters: <max> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    parameters = command_parameters.split(' ')
    if parameters == ['']:
        parameters = []

    if len(parameters) != 1:
        raise ValueError("Invalid parameters from command 'max'.")
    if not parameters[0].isdigit():
        raise ValueError("Apartment number must be a positive integer.")
    display_max_amount_per_each_expense_type_for(expenses_list, int(parameters[0]))


def display_max_amount_per_each_expense_type_for(expenses_list, apartment):
    """
    Displays the string representation of the maximum amount per each expense type for an apartment
    :param expenses_list: an expenses list
    :param apartment: an apartment
    :return: -
    """
    max_amount = max_amount_apartment(expenses_list, apartment)
    print(f"The maximum amount per each expense type for apartment {apartment} is ${max_amount}.")


def sort_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <sort> command
    :param expenses_list: an expenses list
    :param command_parameters: <sort> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    parameters = command_parameters.split(' ')
    if parameters == ['']:
        parameters = []

    if len(parameters) != 1 or (parameters[0] not in ("apartment", "type")):
        raise ValueError("Invalid parameters from command 'sort'.")

    if parameters[0] == "apartment":
        display_apartments_sorted_by_total_amount(expenses_list)
    else:
        display_apartments_sorted_by_expense_type(expenses_list)


def display_apartments_sorted_by_total_amount(expenses_list):
    """
    Displays the list of the string representations of the apartments sorted ascending by total amount of expenses
    :param expenses_list: an expenses list
    :return: -
    """
    sorted_apartments_list = sort_apartments_by_total_amount(expenses_list)
    for apartment in sorted_apartments_list:
        print(apartment_to_str(apartment), end=", " if apartment != sorted_apartments_list[-1]else '\n')


def display_apartments_sorted_by_expense_type(expenses_list):
    """
    Displays the string representation of total amount of expenses for each type, sorted ascending by amount of money
    :param expenses_list: an expenses list
    :return: -
    """
    sorted_expense_type_list = sort_expense_types_by_total_amount(expenses_list)
    for type in sorted_expense_type_list:
        print(f"The total amount of expenses for '{type[0]}' is ${type[1]}.")


def filter_command_ui(expenses_list, command_parameters):
    """
    This is the UI function for <filter> command
    :param expenses_list: an expenses list
    :param command_parameters: <filter> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    expense_type = ["water", "heating", "electricity", "gas", "other"]
    parameters = command_parameters.split(' ')
    if parameters == ['']:
        parameters = []

    if len(parameters) != 1 or (not parameters[0].isdigit() and parameters[0] not in expense_type):
        raise ValueError("Invalid parameters from command 'filter'.")
    if parameters[0].isdigit():
        expenses_list[:] = filter_value(expenses_list, int(parameters[0]))
    else:
        expenses_list[:] = filter_type(expenses_list, parameters[0])


def undo_command_ui(expenses_list, history, command_parameters):
    """
    This is the UI function for <undo> command
    :param expenses_list: an expenses list
    :param history: the history of the expenses lists
    :param command_parameters: <undo> command parameters
    :return: -
    :exception: raises ValueError if the parameters are invalid
    """
    parameters = command_parameters.split(' ')
    if parameters == ['']:
        parameters = []

    if len(parameters) != 0:
        raise ValueError("Invalid parameters from command 'undo'.")
    if not len(history):
        raise ValueError("Cannot do 'undo' command anymore.")

    undo_command(expenses_list, history)


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
    command_word = ''
    expenses_list = create_expenses_list()
    commands = {"add": add_command_ui, "remove": remove_command_ui, "replace": replace_command_ui, "list": list_command_ui, "sum": sum_command_ui,
                "max": max_command_ui, "sort": sort_command_ui, "filter": filter_command_ui, "undo": undo_command_ui}
    done = False
    history = [[]]
    test_init(expenses_list, history)

    while not done:
        try:
            sort_expenses_list(expenses_list)
            command = input('command >').strip()
            command_word, command_parameters = split_command(command)
            if command_word in ["add", "remove", "replace", "filter"]:
                history = add_expenses_list_to_history(expenses_list, history)
            if command_word in commands:
                if command_word == "undo":
                    undo_command_ui(expenses_list, history, command_parameters)
                else:
                    commands[command_word](expenses_list, command_parameters)
            elif "help" == command_word:
                print("List of commands:\n(A) Add new transaction\n1. add <apartment> <type> <amount>\n\n(B) Modify expenses\n2. remove <apartment>")
                print("3. remove <start apartment> to <end apartment>\n4. remove <type>\n5. replace <apartment> <type> with <amount>\n\n(C) Display expenses having different properties")
                print("6. list\n7. list <apartment>\n8. list [ < | = | > ] <amount>\n")
                print("(D) Obtain different characteristics of the expenses\n9. sum <type>\n10. max <apartment>\n11. sort apartment\n12. sort type\n")
                print("(E) Filter\n13. filter <type>\n14. filter <value>\n\n(F) Undo\n15. undo\n")
            elif 'exit' == command_word:
                done = True
            else:
                print("'" + command_word + "'", "is not recognized as a valid command.")
        except ValueError as value_error:
            print(str(value_error))
            if command_word in ["add", "remove", "replace", "filter"]:
                history.pop()
