import unittest

from domain.movie import Movie
from erros.exceptions import ValidationError
from infrastructure.repositories import MovieRepository
from services.movie_service import MovieService
from validation.movie_validator import MovieValidator


class TestMovieService(unittest.TestCase):
    def setUp(self):
        self.__service = MovieService(MovieValidator(), MovieRepository())

    def test_add_movie(self):
        Movie.clear_number_of_instances()
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.assertEqual(self.__service.get_movie(1).title, 'Ion')
        self.assertEqual(self.__service.get_movie(1).description, 'Best one!')
        self.assertEqual(self.__service.get_movie(1).genre, 'Thriller')
        self.assertRaises(ValidationError, self.__service.add_movie, 'Baltagul', 'BAC', '')

    def test_remove_movie(self):
        Movie.clear_number_of_instances()
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.__service.add_movie('Baltagul', 'BAC', 'Thriller')
        self.__service.remove_movie(1)
        self.assertEqual(self.__service.get_all_movies()[0].title, 'Baltagul')
        self.assertEqual(len(self.__service.get_all_movies()), 1)

    def test_update_title(self):
        Movie.clear_number_of_instances()
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.__service.add_movie('Baltagul', 'BAC', 'Thriller')
        self.__service.update_title(1, 'Star Wars')
        self.assertEqual(self.__service.get_movie(1).title, 'Star Wars')

    def test_update_description(self):
        Movie.clear_number_of_instances()
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.__service.add_movie('Baltagul', 'BAC', 'Thriller')
        self.__service.update_description(1, 'Cool.')
        self.assertEqual(self.__service.get_movie(1).description, 'Cool.')

    def test_update_genre(self):
        Movie.clear_number_of_instances()
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.__service.add_movie('Baltagul', 'BAC', 'Thriller')
        self.__service.update_genre(1, 'Love')
        self.assertEqual(self.__service.get_movie(1).genre, 'Love')

    def test_generate_movies(self):
        Movie.clear_number_of_instances()
        self.__service.generate_movies()
        self.assertEqual(len(self.__service.get_all_movies()), 10)
        for i in range(1, 11):
            self.assertEqual(self.__service.get_movie(i).id, i)

    def test_search_by_id(self):
        Movie.clear_number_of_instances()
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.assertEqual(self.__service.search_by_id(1)[0], self.__service.get_all_movies()[0])

    def test_search_by_title(self):
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.assertEqual(self.__service.search_by_title('Ion')[0], self.__service.get_all_movies()[0])

    def test_search_by_description(self):
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.assertEqual(self.__service.search_by_description('OnE')[0], self.__service.get_all_movies()[0])

    def test_search_by_genre(self):
        self.__service.add_movie('Ion', 'Best one!', 'Thriller')
        self.assertEqual(self.__service.search_by_genre('ThrilLeR')[0], self.__service.get_all_movies()[0])
