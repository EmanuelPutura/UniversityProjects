import unittest

from colors.color import Color
from domain.client import Client
from domain.movie import Movie
import datetime

from domain.rental import Rental


class TestClient(unittest.TestCase):
    def test_client(self):
        Client.clear_number_of_instances()
        client_name = 'Michael Smith'
        client = Client(client_name)
        client_str_representation = ' ClientID: {} '.format(client.id).ljust(30, '-').rjust(45, '-') + '\n'
        client_str_representation += "--Name: '{}'\n".format(client.name)
        client_str_representation += ''.rjust(45, '-') + '\n'
        client_str_representation = Color.OKGREEN + client_str_representation + Color.ENDC

        self.assertEqual(client.id, 1)
        self.assertEqual(client.name, client_name)
        self.assertEqual(str(client), client_str_representation)

    def test_gui_str(self):
        Client.clear_number_of_instances()
        client_name = 'Michael Smith'
        client = Client(client_name)
        str_representation = '-' * 5 + ' ClientID: {}'.format(client.id) + '\n'
        str_representation += '-' * 5 + ' Name: {}'.format(client.name) + '\n'
        str_representation += '-' * 100 + '\n'
        self.assertEqual(client.gui_str(), str_representation)


class TestMovie(unittest.TestCase):
    def test_movie(self):
        Movie.clear_number_of_instances()
        movie_title = 'Good Will Hunting'
        movie_description = 'One of the best movies I have ever seen!'
        movie_genre = 'Drama'
        movie1 = Movie(movie_title, movie_description, movie_genre)
        movie_str_representation = ' MovieID: {} '.format(movie1.id).rjust(30, '-').ljust(45, '-') + '\n'
        movie_str_representation += "--Title: '{}'\n".format(movie1.title)
        movie_str_representation += "--Description: '{}'\n".format(movie1.description)
        movie_str_representation += "--Genre: '{}'\n".format(movie1.genre)
        movie_str_representation += ''.rjust(45, '-') + '\n'
        movie_str_representation = Color.OKGREEN + movie_str_representation + Color.ENDC

        self.assertEqual(movie1.id, 1)
        self.assertEqual(movie1.title, movie_title)
        self.assertEqual(movie1.description, movie_description)
        self.assertEqual(movie1.genre, movie_genre)
        self.assertEqual(str(movie1), movie_str_representation)

        Movie.clear_number_of_instances()
        movie2 = Movie(movie_title, movie_description, movie_genre)

        self.assertEqual(movie1, movie2)

        Movie.clear_number_of_instances()
        movie3 = Movie('', '', '')

        self.assertEqual(movie1, movie3)
        self.assertEqual(movie2, movie3)

        movie_title = 'Ion'
        movie_description = 'Mandatory for BAC.'
        movie_genre = 'Thriller'
        movie1.title = movie_title
        movie1.description = movie_description
        movie1.genre = movie_genre

        self.assertEqual(movie1.title, movie_title)
        self.assertEqual(movie1.description, movie_description)
        self.assertEqual(movie1.genre, movie_genre)

    def test_gui_str(self):
        Movie.clear_number_of_instances()
        movie_title = 'Good Will Hunting'
        movie_description = 'One of the best movies I have ever seen!'
        movie_genre = 'Drama'
        movie = Movie(movie_title, movie_description, movie_genre)
        str_representation = '-' * 5 + ' Movie ID: {}'.format(movie.id) + '\n'
        str_representation += '-' * 5 + ' Title: {}'.format(movie.title) + '\n'
        str_representation += '-' * 5 + ' Description: {}'.format(movie.description) + '\n'
        str_representation += '-' * 5 + ' Genre: {}'.format(movie.genre) + '\n'
        str_representation += '-' * 100 + '\n'
        self.assertEqual(movie.gui_str(), str_representation)


class TestRental(unittest.TestCase):
    def test_rental(self):
        rental_movieID = 1
        rental_clientID = 1
        rental_rented_date = datetime.date(2019, 4, 15)
        rental_due_date = datetime.date(2020, 2, 25)
        rental_returned_date = datetime.date(2020, 1, 25)
        default_returned_date = 'Not returned yet.'
        rental = Rental(rental_movieID, rental_clientID, rental_rented_date, rental_due_date)
        rental_str_representation = Color.OKGREEN + "Rental: (Rental ID: {}, Movie ID: {}, Client ID: {}, Rented Date: '{}', " \
                        "Due Date: '{}', Returned Date: '{}')".format(rental.id, rental.movie_id, rental.client_id,
                        rental.rented_date, rental.due_date, rental.returned_date) + Color.ENDC

        self.assertEqual(rental.movie_id, rental_movieID)
        self.assertEqual(rental.client_id, rental_clientID)
        self.assertEqual(rental.rented_date, rental_rented_date)
        self.assertEqual(rental.due_date, rental_due_date)
        self.assertEqual(rental.returned_date, default_returned_date)
        self.assertEqual(str(rental), rental_str_representation)

        rental.returned_date = rental_returned_date
        self.assertEqual(rental.returned_date, rental_returned_date)
