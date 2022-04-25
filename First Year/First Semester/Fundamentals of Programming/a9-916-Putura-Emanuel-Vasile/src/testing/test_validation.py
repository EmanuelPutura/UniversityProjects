import datetime
import unittest

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from erros.exceptions import ValidationError
from validation.client_validator import ClientValidator
from validation.movie_validator import MovieValidator
from validation.rental_validator import RentalValidator


class TestClientValidator(unittest.TestCase):
    def setUp(self):
        self.__validator = ClientValidator()

    def test_client_validator(self):
        Client.clear_number_of_instances()
        client = Client('Anne Bovary')
        client.id = -1
        self.assertRaises(ValidationError, self.__validator.validate, client)
        client.id = 1
        client.name = ''
        self.assertRaises(ValidationError, self.__validator.validate, client)


class TestMovieValidator(unittest.TestCase):
    def setUp(self):
        self.__validator = MovieValidator()

    def test_movie_validator(self):
        Movie.clear_number_of_instances()
        movie = Movie('Baltagul', 'BAC', 'Thriller')
        movie.id = -1
        self.assertRaises(ValidationError, self.__validator.validate, movie)
        movie.id = 1
        movie.title = ''
        self.assertRaises(ValidationError, self.__validator.validate, movie)
        movie.title = 'Ion'
        movie.description = ''
        self.assertRaises(ValidationError, self.__validator.validate, movie)
        movie.description = 'Cool.'
        movie.genre = ''
        self.assertRaises(ValidationError, self.__validator.validate, movie)


class TestRentalValidator(unittest.TestCase):
    def setUp(self):
        self.__validator = RentalValidator()

    def test_rental_validator(self):
        Rental.clear_number_of_instances()
        rental = Rental(1, 1, datetime.date(2020, 2, 28), datetime.date(2020, 7, 1))
        rental.id = -1
        self.assertRaises(ValidationError, self.__validator.validate, rental)
        rental.id = 1
        rental.returned_date = datetime.date(2020, 1, 25)
        self.assertRaises(ValidationError, self.__validator.validate, rental)
