import unittest

from domain.client import Client
from erros.exceptions import ValidationError
from infrastructure.repositories import ClientRepository
from services.client_service import ClientService
from validation.client_validator import ClientValidator


class TestClientService(unittest.TestCase):
    def setUp(self):
        self.__service = ClientService(ClientValidator(), ClientRepository())

    def test_add_client(self):
        Client.clear_number_of_instances()
        self.__service.add_client('Anne Bovary')
        self.assertEqual(self.__service.get_all_clients()[0].name, 'Anne Bovary')
        self.assertRaises(ValidationError, self.__service.add_client, '')

    def test_remove(self):
        Client.clear_number_of_instances()
        self.__service.add_client('Anne Bovary')
        self.__service.add_client('Marie Bolkonsky')
        self.__service.remove_client(1)
        self.assertEqual(self.__service.get_all_clients()[0].name, 'Marie Bolkonsky')

    def test_update_name(self):
        Client.clear_number_of_instances()
        self.__service.add_client('Anne Bovary')
        self.__service.add_client('Marie Bolkonsky')
        self.__service.update_name(1, 'Andre Bovary')
        self.assertEqual(self.__service.get_client(1).name, 'Andre Bovary')

    def test_generate_clients(self):
        Client.clear_number_of_instances()
        self.__service.generate_clients()
        self.assertEqual(len(self.__service.get_all_clients()), 10)
        for i in range(1, 11):
            self.assertEqual(self.__service.get_all_clients()[i - 1].id, i)

    def test_search_by_id(self):
        Client.clear_number_of_instances()
        self.__service.add_client('Anne Bovary')
        self.__service.add_client('Marie Bolkonsky')
        self.assertEqual(self.__service.search_by_id(2)[0], self.__service.get_all_clients()[1])

    def test_search_by_name(self):
        Client.clear_number_of_instances()
        self.__service.add_client('Anne Bovary')
        self.assertEqual(self.__service.search_by_name('nn')[0], self.__service.get_all_clients()[0])
