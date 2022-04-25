from colors.color import Color


class MovieDelayDTO:
    def __init__(self, movie, delay):
        self.__movie = movie
        self.__delay = delay

    @property
    def movie(self):
        return self.__movie

    @property
    def delay(self):
        return self.__delay

    def __str__(self):
        str_representation = ' MovieID: {} '.format(self.__movie.id).rjust(30, '-').ljust(45, '-') + '\n'
        str_representation += "--Title: '{}'\n".format(self.__movie.title)
        str_representation += "--Description: '{}'\n".format(self.__movie.description)
        str_representation += "--Genre: '{}'\n".format(self.__movie.genre)
        str_representation += "--Number of days of delay: {}\n".format(self.__delay)
        str_representation += ''.rjust(45, '-') + '\n'
        return Color.OKGREEN + str_representation + Color.ENDC

    def gui_str(self):
        str_representation = '-' * 5 + ' Movie ID: {}'.format(self.__movie.id) + '\n'
        str_representation += '-' * 5 + ' Title: {}'.format(self.__movie.title) + '\n'
        str_representation += '-' * 5 + ' Description: {}'.format(self.__movie.description) + '\n'
        str_representation += '-' * 5 + ' Genre: {}'.format(self.__movie.genre) + '\n'
        str_representation += '-' * 5 + ' Number of days of delay: {}'.format(self.__delay) + '\n'
        str_representation += '-' * 100 + '\n'
        return str_representation

    def __eq__(self, other):
        return self.__movie == other.movie and self.__delay == other.delay


class MovieDelayAssembler:
    @staticmethod
    def create_dto(movie, delay):
        return MovieDelayDTO(movie, delay)
