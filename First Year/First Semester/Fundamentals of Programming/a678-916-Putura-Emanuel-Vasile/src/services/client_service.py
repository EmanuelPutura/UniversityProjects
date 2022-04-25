from domain.client import Client
from random import randint


class ClientService:
    """
    Service class for the Client class
    """
    def __init__(self, client_validator, client_repository):
        self.__client_validator = client_validator
        self.__client_repository = client_repository

    def add_client(self, name):
        """
        Adds a new client
        :param name: the client's name
        :return: the added client
        """
        client = Client(name)
        self.__client_validator.validate(client)
        self.__client_repository.add(client)
        return client

    def remove_client(self, client_id):
        """
        Removes a client
        :param client_id: the client's ID
        :return: -
        """
        self.__client_repository.remove(client_id)

    def update_name(self, client_id, name):
        """
        Updates a client's name
        :param client_id: the client's ID
        :param name: the client's new name
        :return: -
        """
        self.__client_repository.update_name(client_id, name)

    def search_by_id(self, id):
        """
        Searches clients by a given ID
        :param id: a given ID
        :return: the list of found clients
        """
        return self.__client_repository.search_by_id(id)

    def search_by_name(self, name):
        """
        Searches clients by a given name
        :param name: a given name
        :return: the list of found clients
        """
        return self.__client_repository.search_by_name(name)

    def get_all_clients(self):
        """
        Gets all the existing clients
        :return: all the existing clients
        """
        return self.__client_repository.entities

    def get_client(self, client_id):
        """
        Gets a client, being given its ID
        :param client_id: the client's ID
        :return: the client, if it exists
        """
        return self.__client_repository.find_by_id(client_id)

    def generate_clients(self):
        """
        Generate random clients
        """
        number_of_clients = 10
        default_names = ['Gigi Becali', 'Donald Trump', 'Bill Gates', 'Vladimir Putin', 'Harry Potter', 'Florinel Coman',
                         'Gill Bates', 'Cristi Tanase', 'Obama', 'Gigel Costea', 'Mihai Marai', 'Mihai Stoichita', 'Misu Pop',
                         'Tonald Drump', 'Bibi Gecali', 'Viktor Andrew', 'Victor Pop', 'Joe Biden', 'Joe Andrew', 'Lionel Messi']
        clients = self.__client_repository.entities
        client_names = list(map(lambda client: client.name, clients))

        for i in range(number_of_clients):
            while True:
                name = default_names[randint(0, len(default_names) - 1)]
                if not (name in client_names):
                    client_names.append(name)
                    break
            self.add_client(name)
