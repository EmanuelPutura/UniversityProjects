from colors.color import Color


class MovieRentalDTO:
    def __init__(self, movie, number_of_rented_days):
        self.__movie = movie
        self.__number_of_rented_days = number_of_rented_days

    @property
    def movie(self):
        return self.__movie

    @property
    def number_of_rented_days(self):
        return self.__number_of_rented_days

    def __str__(self):
        str_representation = ' MovieID: {} '.format(self.__movie.id).rjust(30, '-').ljust(45, '-') + '\n'
        str_representation += "--Title: '{}'\n".format(self.__movie.title)
        str_representation += "--Description: '{}'\n".format(self.__movie.description)
        str_representation += "--Genre: '{}'\n".format(self.__movie.genre)
        str_representation += "--Number of rented days: {}\n".format(self.__number_of_rented_days)
        str_representation += ''.rjust(45, '-') + '\n'
        return Color.OKGREEN + str_representation + Color.ENDC

    def gui_str(self):
        str_representation = '-' * 5 + ' Movie ID: {}'.format(self.__movie.id) + '\n'
        str_representation += '-' * 5 + ' Title: {}'.format(self.__movie.title) + '\n'
        str_representation += '-' * 5 + ' Description: {}'.format(self.__movie.description) + '\n'
        str_representation += '-' * 5 + ' Genre: {}'.format(self.__movie.genre) + '\n'
        str_representation += '-' * 5 + ' Number of rented days: {}'.format(self.__number_of_rented_days) + '\n'
        str_representation += '-' * 100 + '\n'
        return str_representation

    def __eq__(self, other):
        return self.__movie == other.movie and self.__number_of_rented_days == other.number_of_rented_days


class MovieRentalAssembler:
    @staticmethod
    def create_dto(movie, number_of_rented_days):
        return MovieRentalDTO(movie, number_of_rented_days)
