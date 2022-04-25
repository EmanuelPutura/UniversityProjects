import unittest

from domain.movie import Movie
from iterators.collection import Collection, filter_data, comb_sort


class TestCollection(unittest.TestCase):
    def setUp(self):
        self.__collection = Collection()

    def test_collection(self):
        movie1 = Movie('Title1', 'Description1', 'Genre1')
        movie1.id = 2
        movie2 = Movie('Title2', 'Description2', 'Genre2')
        movie2.id = 1
        movie3 = Movie('Title3', 'Description3', 'Genre3')
        movie3.id = 7
        movie4 = Movie('Title4', 'Description4', 'Genre4')
        movie4.id = 10
        movie5 = Movie('Title5', 'Description5', 'Genre5')
        movie5.id = 5

        movies = [movie1, movie2, movie3, movie4, movie5]

        self.__collection.append(movie1)
        self.__collection.append(movie2)
        self.__collection.append(movie3)
        self.__collection.append(movie4)
        self.__collection.append(movie5)

        index = 0
        for movie in self.__collection:
            self.assertEqual(movie, movies[index])
            index += 1

        self.assertEqual(self.__collection.data, movies)
        self.assertEqual(self.__collection[2], movie3)

        self.__collection[2] = movie4
        self.assertEqual(self.__collection[2], movie4)

        del self.__collection[2]
        self.assertEqual(self.__collection[2], movie4)

        self.__collection.remove(movie4)
        self.assertEqual(self.__collection[2], movie5)


class TestFilter(unittest.TestCase):
    def test_filter(self):
        movie1 = Movie('Title1', 'Description1', 'Genre1')
        movie1.id = 2
        movie2 = Movie('Title2', 'Description2', 'Genre2')
        movie2.id = 1
        movie3 = Movie('Title3', 'Description3', 'Genre3')
        movie3.id = 7
        movie4 = Movie('Title4', 'Description4', 'Genre4')
        movie4.id = 10
        movie5 = Movie('Title5', 'Description5', 'Genre5')
        movie5.id = 5

        collection = Collection()

        collection.append(movie1)
        collection.append(movie2)
        collection.append(movie3)
        collection.append(movie4)
        collection.append(movie5)

        filtered_movies = [movie1, movie4]
        index = 0

        collection = filter_data(collection, lambda movie: movie.id % 2 == 0)
        for movie in collection:
            self.assertEqual(movie, filtered_movies[index])
            index += 1


class TestCombSort(unittest.TestCase):
    def test_comb_sort(self):
        movie1 = Movie('Title1', 'Description1', 'Genre1')
        movie1.id = 2
        movie2 = Movie('Title2', 'Description2', 'Genre2')
        movie2.id = 1
        movie3 = Movie('Title3', 'Description3', 'Genre3')
        movie3.id = 7
        movie4 = Movie('Title4', 'Description4', 'Genre4')
        movie4.id = 10
        movie5 = Movie('Title5', 'Description5', 'Genre5')
        movie5.id = 5

        collection = Collection()

        collection.append(movie1)
        collection.append(movie2)
        collection.append(movie3)
        collection.append(movie4)
        collection.append(movie5)

        sorted_movies = [movie2, movie1, movie5, movie3, movie4]
        index = 0

        comb_sort(collection, lambda movie1, movie2: movie1.id < movie2.id)

        for movie in collection:
            self.assertEqual(movie, sorted_movies[index])
            index += 1
