import unittest

from domain.client import Client
from erros.exceptions import RepositoryError
from infrastructure.repositories import Repository


class TestRepository(unittest.TestCase):
    def setUp(self):
        Client.clear_number_of_instances()
        client1 = Client('John Smith')
        client2 = Client('Marry Jones')
        client3 = Client('Andrew Stevens')
        client4 = Client('John Clinton')
        client5 = Client('Margaret Adams')
        self.__repository = Repository()
        self.__repository.add(client1)
        self.__repository.add(client2)
        self.__repository.add(client3)
        self.__repository.add(client4)
        self.__repository.add(client5)

    def test_repository(self):
        repository = Repository()
        self.assertEqual(repository.entities, [])

    def test_add(self):
        Client.clear_number_of_instances()
        repository = Repository()
        client = Client('John Smith')
        repository.add(client)
        Client.clear_number_of_instances()
        self.assertEqual(repository.entities, [client])
        self.assertEqual(len(repository), 1)
        self.assertRaises(RepositoryError, repository.add, Client('Thomas Smiths'))

    def test_find_by_id(self):
        self.assertEqual(self.__repository.find_by_id(1), self.__repository.entities[0])
        self.assertEqual(self.__repository.find_by_id(6), None)

    def test_remove(self):
        entities = self.__repository.entities
        self.assertRaises(RepositoryError, self.__repository.remove, len(self.__repository) + 1)
        self.__repository.remove(1)
        self.assertEqual(len(self.__repository), 4)
        self.assertEqual(self.__repository.entities, entities[1:])

    def test_search_by_id(self):
        entities = self.__repository.entities
        self.assertEqual(self.__repository.search_by_id(1)[0], entities[0])
