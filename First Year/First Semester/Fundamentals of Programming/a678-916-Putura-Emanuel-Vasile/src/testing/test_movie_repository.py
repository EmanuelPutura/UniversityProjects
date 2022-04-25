import unittest

from domain.movie import Movie
from erros.exceptions import RepositoryError
from infrastructure.repositories import MovieRepository


class TestMovieRepository(unittest.TestCase):
    def setUp(self):
        self.__repository = MovieRepository()
        Movie.clear_number_of_instances()
        movie = Movie('Baltagul', 'BAC', 'Thriller')
        self.__repository.add(movie)

    def test_update_title(self):
        self.__repository.update_title(1, 'Ion')
        self.assertEqual(self.__repository.entities[0].title, 'Ion')
        self.assertRaises(RepositoryError, self.__repository.update_title, 2, 'Ion')

    def test_update_description(self):
        self.__repository.update_description(1, 'Best one!')
        self.assertEqual(self.__repository.entities[0].description, 'Best one!')
        self.assertRaises(RepositoryError, self.__repository.update_description, -1, 'Cool!')

    def test_update_genre(self):
        self.__repository.update_genre(1, 'War')
        self.assertEqual(self.__repository.entities[0].genre, 'War')
        self.assertRaises(RepositoryError, self.__repository.update_genre, 0, 'Love')

    def test_search_by_title(self):
        self.__repository.add(Movie('Ion', 'Cool.', 'Love'))
        self.assertEqual(self.__repository.search_by_title('Ion')[0], self.__repository.entities[1])

    def test_search_by_description(self):
        self.__repository.add(Movie('Ion', 'Cool.', 'Love'))
        self.assertEqual(self.__repository.search_by_description('Co')[0], self.__repository.entities[1])

    def test_by_genre(self):
        self.__repository.add(Movie('Ion', 'Cool', 'Western'))
        self.assertEqual(self.__repository.search_by_genre('er'), self.__repository.entities)
