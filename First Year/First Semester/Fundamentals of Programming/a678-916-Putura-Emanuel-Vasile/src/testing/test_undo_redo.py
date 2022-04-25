import datetime
import unittest

from infrastructure.repositories import MovieRepository, ClientRepository, RentalRepository
from services.client_service import ClientService
from services.movie_service import MovieService
from services.rental_service import RentalService
from services.undo_redo_handlers import UndoHandlerEnum
from services.undo_redo_service import UndoManager, RedoManager
from validation.client_validator import ClientValidator
from validation.movie_validator import MovieValidator
from validation.rental_validator import RentalValidator


class TestUndoRedo(unittest.TestCase):
    def setUp(self):
        self.__movie_repository = MovieRepository()
        self.__movie_service = MovieService(MovieValidator(), self.__movie_repository)
        self.__client_repository = ClientRepository()
        self.__client_service = ClientService(ClientValidator(), self.__client_repository)
        self.__rental_service = RentalService(RentalValidator(), RentalRepository(), self.__movie_repository, self.__client_repository)

    def test_undo_redo(self):
        movie = self.__movie_service.add_movie('Ion', 'Cool!', 'Thriller')
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.ADD_MOVIE, movie.id, self.__rental_service)
        UndoManager.undo()
        self.assertEqual(len(self.__movie_service.get_all_movies()), 0)
        RedoManager.redo()
        self.assertEqual(len(self.__movie_service.get_all_movies()), 1)

        self.__movie_service.remove_movie(movie.id)
        removed_rentals = self.__rental_service.remove_movie_rentals(movie.id)
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.REMOVE_MOVIE, movie,
                                       removed_rentals, self.__rental_service)
        UndoManager.undo()
        self.assertEqual(len(self.__movie_service.get_all_movies()), 1)
        RedoManager.redo()
        self.assertEqual(len(self.__movie_service.get_all_movies()), 0)
        UndoManager.undo()

        movie_title = movie.title
        movie_description = movie.description
        movie_genre = movie.genre

        self.__movie_service.update_title(movie.id, 'Mara')
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.UPDATE_MOVIE_TITLE, movie.id, movie_title)
        UndoManager.undo()
        self.assertEqual(self.__movie_service.get_all_movies()[0].title, movie_title)
        RedoManager.redo()
        self.assertEqual(self.__movie_service.get_all_movies()[0].title, 'Mara')

        self.__movie_service.update_description(movie.id, 'Very nice!')
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.UPDATE_MOVIE_DESCRIPTION, movie.id, movie_description)
        UndoManager.undo()
        self.assertEqual(self.__movie_service.get_all_movies()[0].description, movie_description)
        RedoManager.redo()
        self.assertEqual(self.__movie_service.get_all_movies()[0].description, 'Very nice!')

        self.__movie_service.update_genre(movie.id, 'Action')
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.UPDATE_MOVIE_GENRE, movie.id, movie_genre)
        UndoManager.undo()
        self.assertEqual(self.__movie_service.get_all_movies()[0].genre, movie_genre)
        RedoManager.redo()
        self.assertEqual(self.__movie_service.get_all_movies()[0].genre, 'Action')

        client = self.__client_service.add_client('Ion')
        UndoManager.register_operation(self.__client_service, UndoHandlerEnum.ADD_CLIENT, client.id, self.__rental_service)
        UndoManager.undo()
        self.assertEqual(len(self.__client_service.get_all_clients()), 0)
        RedoManager.redo()
        self.assertEqual(len(self.__client_service.get_all_clients()), 1)

        self.__client_service.remove_client(client.id)
        removed_rentals = self.__rental_service.remove_client_rentals(client.id)
        UndoManager.register_operation(self.__client_service, UndoHandlerEnum.REMOVE_CLIENT, client,
                                       removed_rentals, self.__rental_service)
        UndoManager.undo()
        self.assertEqual(len(self.__client_service.get_all_clients()), 1)
        RedoManager.redo()
        self.assertEqual(len(self.__client_service.get_all_clients()), 0)
        UndoManager.undo()

        client_name = client.name
        self.__client_service.update_name(client.id, 'Gigel')
        UndoManager.register_operation(self.__client_service, UndoHandlerEnum.UPDATE_CLIENT_NAME, client.id, client_name)
        UndoManager.undo()
        self.assertEqual(self.__client_service.get_all_clients()[0].name, client_name)
        RedoManager.redo()
        self.assertEqual(self.__client_service.get_all_clients()[0].name, 'Gigel')

        rental = self.__rental_service.add_rental(1, 1, datetime.date(2020, 3, 26), datetime.date(2020, 4, 27))
        UndoManager.register_operation(self.__rental_service, UndoHandlerEnum.RENT_MOVIE, rental.id)
        UndoManager.undo()
        self.assertEqual(len(self.__rental_service.get_all_rentals()), 0)
        RedoManager.redo()
        self.assertEqual(len(self.__rental_service.get_all_rentals()), 1)

        self.__rental_service.update_returned_date(rental.id, datetime.date(2020, 4, 28))
        UndoManager.register_operation(self.__rental_service, UndoHandlerEnum.RETURN_MOVIE, rental.id)
        UndoManager.undo()
        self.assertEqual(self.__rental_service.get_all_rentals()[0].returned_date, rental.returned_date)
        RedoManager.redo()
        self.assertEqual(self.__rental_service.get_all_rentals()[0].returned_date, datetime.date(2020, 4, 28))
