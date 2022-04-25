import json
import os


from datetime import *

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from infrastructure.memory_repositories import MovieRepository, ClientRepository, RentalRepository


class MovieJSONRepository(MovieRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file()
        self.__load_json()

    def __create_file(self):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_json(self):
        if os.path.getsize(self.__file_name) == 0:
            return
        with open(self.__file_name, 'r') as json_file:
            movie_data = json.load(json_file)
            for data_dictionary in movie_data['movie_list']:
                movie = Movie(data_dictionary['title'],
                                               data_dictionary['description'],
                                               data_dictionary['genre'])
                movie.id = data_dictionary['id']
                super().add(movie)

    def __save_json(self):
        with open(self.__file_name, 'w') as json_file:
            json_data = {'movie_list': []}
            for movie in self.entities:
                json_data['movie_list'].append(
                    {
                        'id': movie.id,
                        'title': movie.title,
                        'description': movie.description,
                        'genre': movie.genre
                    }
                )
            json.dump(json_data, json_file, indent=4, separators=(", ", ": "), sort_keys=False)

    def add(self, movie):
        movie_id = super().find_next_id()
        movie.id = movie_id
        super().add(movie)
        self.__save_json()

    def remove(self, movie_id):
        super().remove(movie_id)
        self.__save_json()

    def update_title(self, movie_id, title):
        super().update_title(movie_id, title)
        self.__save_json()

    def update_description(self, movie_id, description):
        super().update_description(movie_id, description)
        self.__save_json()

    def update_genre(self, movie_id, genre):
        super().update_genre(movie_id, genre)
        self.__save_json()


class ClientJSONRepository(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file()
        self.__load_json()

    def __create_file(self):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_json(self):
        if os.path.getsize(self.__file_name) == 0:
            return
        with open(self.__file_name, 'r') as json_file:
            client_data = json.load(json_file)
            for data_dictionary in client_data['client_list']:
                client = Client(data_dictionary['name'])
                client.id = data_dictionary['id']
                super().add(client)

    def __save_json(self):
        with open(self.__file_name, 'w') as json_file:
            json_data = {'client_list': []}
            for client in self.entities:
                json_data['client_list'].append(
                    {
                        'id': client.id,
                        'name': client.name
                    }
                )
            json.dump(json_data, json_file, indent=4, separators=(", ", ": "), sort_keys=False)

    def add(self, client):
        client_id = super().find_next_id()
        client.id = client_id
        super().add(client)
        self.__save_json()

    def remove(self, client_id):
        super().remove(client_id)
        self.__save_json()

    def update_name(self, client_id, name):
        super().update_name(client_id, name)
        self.__save_json()


class RentalJSONRepository(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file()
        self.__load_json()

    def __create_file(self):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_json(self):
        if os.path.getsize(self.__file_name) == 0:
            return
        with open(self.__file_name, 'r') as json_file:
            rental_data = json.load(json_file)
            for data_dictionary in rental_data['rental_list']:
                returned_date = 'Not returned yet.'
                if data_dictionary['returned_date'] != 'Not returned yet.':
                    returned_date = datetime.strptime(data_dictionary['returned_date'], '%Y-%m-%d').date()
                rental = Rental(data_dictionary['movie_id'],
                                data_dictionary['client_id'],
                                datetime.strptime(data_dictionary['rented_date'], '%Y-%m-%d').date(),
                                datetime.strptime(data_dictionary['due_date'], '%Y-%m-%d').date(),
                                returned_date
                                )
                rental.id = data_dictionary['id']
                super().add(rental)

    def __save_json(self):
        with open(self.__file_name, 'w') as json_file:
            rental_data = {'rental_list': []}
            for rental in self.entities:
                rental_data['rental_list'].append(
                    {
                        'id': rental.id,
                        'movie_id': rental.movie_id,
                        'client_id': rental.client_id,
                        'rented_date': str(rental.rented_date),
                        'due_date': str(rental.due_date),
                        'returned_date': str(rental.returned_date)
                    }
                )
            json.dump(rental_data, json_file, indent=4, separators=(", ", ": "), sort_keys=False)

    def add(self, rental):
        rental_id = super().find_next_id()
        rental.id = rental_id
        super().add(rental)
        self.__save_json()

    def remove(self, rental_id):
        super().remove(rental_id)
        self.__save_json()

    def update_returned_date(self, rental_id, returned_date):
        super().update_returned_date(rental_id, returned_date)
        self.__save_json()
