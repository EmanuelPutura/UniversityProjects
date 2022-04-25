import unittest

from colors.color import Color
from domain.client import Client
from domain.movie import Movie
from services.client_rental_dto import ClientRentalAssembler
from services.movie_delay_dto import MovieDelayAssembler
from services.movie_rental_dto import MovieRentalAssembler


class TestClientRentalDTO(unittest.TestCase):
    def setUp(self):
        client = Client('Gigi Becali')
        rental_days_number = 30
        self.__client_dto = ClientRentalAssembler.create_dto(client, rental_days_number)

    def test_str(self):
        str_representation = ' ClientID: {} '.format(self.__client_dto.client.id).ljust(30, '-').rjust(45, '-') + '\n'
        str_representation += "--Name: '{}'\n".format(self.__client_dto.client.name)
        str_representation += "--Number of movie rental days: {}\n".format(self.__client_dto.rental_days_number)
        str_representation += ''.rjust(45, '-') + '\n'
        str_representation = Color.OKGREEN + str_representation + Color.ENDC
        self.assertEqual(str(self.__client_dto), str_representation)

    def test_gui_str(self):
        str_representation = '-' * 5 + ' Client ID: {}'.format(self.__client_dto.client.id) + '\n'
        str_representation += '-' * 5 + ' Name: {}'.format(self.__client_dto.client.name) + '\n'
        str_representation += '-' * 5 + 'Number of movie rental days: {}'.format(self.__client_dto.rental_days_number) + '\n'
        str_representation += '-' * 100 + '\n'
        self.assertEqual(self.__client_dto.gui_str(), str_representation)


class TestMovieRentalDTO(unittest.TestCase):
    def setUp(self):
        movie = Movie('Ion', 'Cool.', 'Thriller')
        number_of_rented_days = 30
        self.__movie_dto = MovieRentalAssembler.create_dto(movie, number_of_rented_days)

    def test_str(self):
        str_representation = ' MovieID: {} '.format(self.__movie_dto.movie.id).rjust(30, '-').ljust(45, '-') + '\n'
        str_representation += "--Title: '{}'\n".format(self.__movie_dto.movie.title)
        str_representation += "--Description: '{}'\n".format(self.__movie_dto.movie.description)
        str_representation += "--Genre: '{}'\n".format(self.__movie_dto.movie.genre)
        str_representation += "--Number of rented days: {}\n".format(self.__movie_dto.number_of_rented_days)
        str_representation += ''.rjust(45, '-') + '\n'
        str_representation = Color.OKGREEN + str_representation + Color.ENDC
        self.assertEqual(str(self.__movie_dto), str_representation)

    def test_gui_str(self):
        str_representation = '-' * 5 + ' Movie ID: {}'.format(self.__movie_dto.movie.id) + '\n'
        str_representation += '-' * 5 + ' Title: {}'.format(self.__movie_dto.movie.title) + '\n'
        str_representation += '-' * 5 + ' Description: {}'.format(self.__movie_dto.movie.description) + '\n'
        str_representation += '-' * 5 + ' Genre: {}'.format(self.__movie_dto.movie.genre) + '\n'
        str_representation += '-' * 5 + ' Number of rented days: {}'.format(self.__movie_dto.number_of_rented_days) + '\n'
        str_representation += '-' * 100 + '\n'
        self.assertEqual(self.__movie_dto.gui_str(), str_representation)


class TestMovieDelayDTO(unittest.TestCase):
    def setUp(self):
        movie = Movie('Ion', 'Cool.', 'Thriller')
        delay = 30
        self.__movie_dto = MovieDelayAssembler.create_dto(movie, delay)

    def test_str(self):
        str_representation = ' MovieID: {} '.format(self.__movie_dto.movie.id).rjust(30, '-').ljust(45, '-') + '\n'
        str_representation += "--Title: '{}'\n".format(self.__movie_dto.movie.title)
        str_representation += "--Description: '{}'\n".format(self.__movie_dto.movie.description)
        str_representation += "--Genre: '{}'\n".format(self.__movie_dto.movie.genre)
        str_representation += "--Number of days of delay: {}\n".format(self.__movie_dto.delay)
        str_representation += ''.rjust(45, '-') + '\n'
        str_representation = Color.OKGREEN + str_representation + Color.ENDC
        self.assertEqual(str(self.__movie_dto), str_representation)

    def test_gui_str(self):
        str_representation = '-' * 5 + ' Movie ID: {}'.format(self.__movie_dto.movie.id) + '\n'
        str_representation += '-' * 5 + ' Title: {}'.format(self.__movie_dto.movie.title) + '\n'
        str_representation += '-' * 5 + ' Description: {}'.format(self.__movie_dto.movie.description) + '\n'
        str_representation += '-' * 5 + ' Genre: {}'.format(self.__movie_dto.movie.genre) + '\n'
        str_representation += '-' * 5 + ' Number of days of delay: {}'.format(self.__movie_dto.delay) + '\n'
        str_representation += '-' * 100 + '\n'
        self.assertEqual(self.__movie_dto.gui_str(), str_representation)
