import unittest

from domain.client import Client
from erros.exceptions import RepositoryError
from infrastructure.repositories import ClientRepository


class TestClientRepository(unittest.TestCase):
    def test_update_name(self):
        repository = ClientRepository()
        Client.clear_number_of_instances()
        client = Client('Lucy West')
        repository.add(client)
        repository.update_name(1, 'Marry West')
        self.assertEqual(client.name, 'Marry West')
        self.assertRaises(RepositoryError, repository.update_name, 2, 'Anna West')

    def test_search_by_name(self):
        repository = ClientRepository()
        Client.clear_number_of_instances()
        client = Client('Lucy West')
        repository.add(client)
        self.assertEqual(repository.search_by_name(' Wes')[0], client)
