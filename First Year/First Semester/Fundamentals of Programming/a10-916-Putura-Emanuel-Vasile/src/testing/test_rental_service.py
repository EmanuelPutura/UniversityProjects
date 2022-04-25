import unittest
import datetime

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from erros.exceptions import ValidationError, ServiceError
from infrastructure.memory_repositories import RentalRepository, MovieRepository, ClientRepository
from services.client_rental_dto import ClientRentalAssembler
from services.movie_delay_dto import MovieDelayAssembler
from services.movie_rental_dto import MovieRentalAssembler
from services.rental_service import RentalService
from validation.rental_validator import RentalValidator


class TestRentalService(unittest.TestCase):
    def setUp(self):
        Movie.clear_number_of_instances()
        movie = Movie('Ion', 'BAC', 'Thriller')
        movie_repository = MovieRepository()
        movie_repository.add(movie)
        Client.clear_number_of_instances()
        client = Client('Florin Tanase')
        client_repository = ClientRepository()
        client_repository.add(client)
        self.__service = RentalService(RentalValidator(), RentalRepository(), movie_repository, client_repository)

    def test_add_rental(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        self.assertEqual(self.__service.get_all_rentals()[0].id, 1)
        self.assertEqual(self.__service.get_all_rentals()[0].movie_id, 1)
        self.assertEqual(self.__service.get_all_rentals()[0].client_id, 1)
        self.assertEqual(self.__service.get_all_rentals()[0].rented_date, datetime.date(2020, 3, 26))
        self.assertEqual(self.__service.get_all_rentals()[0].due_date, datetime.date(2020, 4, 27))
        self.assertEqual(self.__service.get_all_rentals()[0].returned_date, 'Not returned yet.')
        self.assertRaises(ValidationError, self.__service.add_rental, 1, 1, datetime.date(2020, 4, 27), datetime.date(2020, 3, 26))
        self.assertRaises(ValidationError, self.__service.add_rental, 1, 1, datetime.date(2020, 4, 27),
                          datetime.date(2020, 3, 26), datetime.date(2020, 2, 27))
        # movie already rented error
        self.assertRaises(ServiceError, self.__service.add_rental, 1, 4, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        self.__service.add_rental(3, 4, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        # movie not returned on time error
        self.assertRaises(ServiceError, self.__service.add_rental, 2, 4, datetime.date(2020, 4, 28), datetime.date(2021, 4, 28))

    def test_update_returned_date(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        self.__service.update_returned_date(1, datetime.date(2020, 3, 28))
        self.assertEqual(self.__service.get_all_rentals()[0].returned_date, datetime.date(2020, 3, 28))

    def test_find_and_update_rental(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(11, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        self.__service.find_and_update_rental(1, 11, datetime.date(2021, 3, 26))
        self.assertEqual(self.__service.get_all_rentals()[0].returned_date, datetime.date(2021, 3, 26))
        self.assertRaises(ServiceError, self.__service.find_and_update_rental, 1, 2, datetime.date(2021, 3, 26))

    def test_find_most_rented_movies(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        delta = (datetime.date.today() - datetime.date(2020, 3, 26)).days
        Movie.clear_number_of_instances()
        movie = Movie('Ion', 'BAC', 'Thriller')
        movie_dto = MovieRentalAssembler.create_dto(movie, delta)
        self.assertEqual(self.__service.find_most_rented_movies()[0], movie_dto)
        self.__service.update_returned_date(1, datetime.date(2020, 4, 28))
        delta = (datetime.date(2020, 4, 28) - datetime.date(2020, 3, 26)).days
        movie_dto = MovieRentalAssembler.create_dto(movie, delta)
        self.assertEqual(self.__service.find_most_rented_movies()[0], movie_dto)

    def test_find_most_active_clients(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        delta = (datetime.date.today() - datetime.date(2020, 3, 26)).days
        Client.clear_number_of_instances()
        client = Client('Florin Tanase')
        client_dto = ClientRentalAssembler.create_dto(client, delta)
        self.assertEqual(self.__service.find_most_active_clients()[0], client_dto)
        self.__service.update_returned_date(1, datetime.date(2020, 4, 28))
        delta = (datetime.date(2020, 4, 28) - datetime.date(2020, 3, 26)).days
        client_dto = ClientRentalAssembler.create_dto(client, delta)
        self.assertEqual(self.__service.find_most_active_clients()[0], client_dto)

    def test_find_late_rentals(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        delta = (datetime.date.today() - datetime.date(2020, 4, 27)).days
        Movie.clear_number_of_instances()
        movie = Movie('Ion', 'BAC', 'Thriller')
        movie_dto = MovieDelayAssembler.create_dto(movie, delta)
        self.assertEqual(self.__service.find_late_rentals()[0], movie_dto)
        self.__service.update_returned_date(1, datetime.date(2020, 4, 28))
        self.assertEqual(len(self.__service.find_late_rentals()), 1)

    def test_remove_movie_rentals(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        self.__service.remove_movie_rentals(1)
        self.assertEqual(len(self.__service.get_all_rentals()), 0)

    def test_remove_client_rentals(self):
        Rental.clear_number_of_instances()
        self.__service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        self.__service.remove_client_rentals(1)
        self.assertEqual(len(self.__service.get_all_rentals()), 0)
