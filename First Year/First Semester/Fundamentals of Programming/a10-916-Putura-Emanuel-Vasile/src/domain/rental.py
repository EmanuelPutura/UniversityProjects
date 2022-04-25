from colors.color import Color


class Rental:
    """
    Represents an abstract type for a rental
    """
    # the ID of a rental is automatically generated
    __number_of_instances = 0

    def __init__(self, movie_id, client_id, rented_date, due_date, returned_date='Not returned yet.'):
        Rental.__number_of_instances += 1
        self.__rental_id = Rental.__number_of_instances
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rented_date = rented_date
        self.__due_date = due_date
        self.__returned_date = returned_date

    @property
    def id(self):
        return self.__rental_id

    @id.setter
    def id(self, new_id):
        self.__rental_id = new_id

    @property
    def movie_id(self):
        return self.__movie_id

    @property
    def client_id(self):
        return self.__client_id

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def due_date(self):
        return self.__due_date

    @property
    def returned_date(self):
        return self.__returned_date

    @returned_date.setter
    def returned_date(self, new_returned_date):
        self.__returned_date = new_returned_date

    @staticmethod
    def clear_number_of_instances():
        """
        Set the value of number_of_instances to zero
        """
        Rental.__number_of_instances = 0

    def __str__(self):
        """
        :return: the string representation of a rental
        """
        return Color.OKGREEN + "Rental: (Rental ID: {}, Movie ID: {}, Client ID: {}, Rented Date: '{}', Due Date: '{}', Returned Date: '{}')".format(
            self.__rental_id, self.__movie_id, self.__client_id, self.__rented_date, self.__due_date, self.__returned_date) + Color.ENDC
