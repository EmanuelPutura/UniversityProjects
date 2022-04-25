from colors.color import Color


class Movie:
    """
    Represents an abstract type for a movie
    """
    # the ID of a movie is automatically generated
    __number_of_instances = 0

    def __init__(self, title, description, genre):
        Movie.__number_of_instances += 1
        self.__movie_id = Movie.__number_of_instances
        self.__title = title
        self.__description = description
        self.__genre = genre

    @property
    def id(self):
        return self.__movie_id

    @id.setter
    def id(self, new_id):
        self.__movie_id = new_id

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, new_title):
        self.__title = new_title

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, new_description):
        self.__description = new_description

    @property
    def genre(self):
        return self.__genre

    @genre.setter
    def genre(self, new_genre):
        self.__genre = new_genre

    @staticmethod
    def clear_number_of_instances():
        """
        Set the value of number_of_instances to zero
        """
        Movie.__number_of_instances = 0

    def __str__(self):
        """
        :return: the string representation of a movie
        """
        str_representation = ' MovieID: {} '.format(self.__movie_id).rjust(30, '-').ljust(45, '-') + '\n'
        str_representation += "--Title: '{}'\n".format(self.__title)
        str_representation += "--Description: '{}'\n".format(self.__description)
        str_representation += "--Genre: '{}'\n".format(self.__genre)
        str_representation += ''.rjust(45, '-') + '\n'
        return Color.OKGREEN + str_representation + Color.ENDC

    def gui_str(self):
        str_representation = '-' * 5 + ' Movie ID: {}'.format(self.__movie_id) + '\n'
        str_representation += '-' * 5 + ' Title: {}'.format(self.__title) + '\n'
        str_representation += '-' * 5 + ' Description: {}'.format(self.__description) + '\n'
        str_representation += '-' * 5 + ' Genre: {}'.format(self.__genre) + '\n'
        str_representation += '-' * 100 + '\n'
        return str_representation

    def __eq__(self, other):
        """
        Checks if two movies are equal (that is, they have the same ID)
        :param other: another movie
        :return: True if the two movies have the same ID, False else
        """
        return self.__movie_id == other.id
