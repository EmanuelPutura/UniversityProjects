from colors.color import Color


class Client:
    """
    Represents an abstract type for a client
    """
    # the ID of a client is automatically generated
    __number_of_instances = 0

    def __init__(self, name):
        Client.__number_of_instances += 1
        self.__client_id = Client.__number_of_instances
        self.__name = name

    @property
    def id(self):
        return self.__client_id

    @id.setter
    def id(self, new_id):
        self.__client_id = new_id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    @staticmethod
    def clear_number_of_instances():
        """
        Set the value of number_of_instances to zero
        """
        Client.__number_of_instances = 0

    def __str__(self):
        """
        :return: the string representation of a client
        """
        str_representation = ' ClientID: {} '.format(self.__client_id).ljust(30, '-').rjust(45, '-') + '\n'
        str_representation += "--Name: '{}'\n".format(self.__name)
        str_representation += ''.rjust(45, '-') + '\n'
        return Color.OKGREEN + str_representation + Color.ENDC

    def gui_str(self):
        str_representation = '-' * 5 + ' ClientID: {}'.format(self.__client_id) + '\n'
        str_representation += '-' * 5 + ' Name: {}'.format(self.__name) + '\n'
        str_representation += '-' * 100 + '\n'
        return str_representation

    def __eq__(self, other):
        """
        Checks if two clients are equal (that is, they have the same ID)
        :param other: another client
        :return: True if the two clients have the same ID, False else
        """
        return self.__client_id == other.id
