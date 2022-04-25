import pickle

from domain.client import Client
from domain.movie import Movie
from domain.rental import Rental
from infrastructure.memory_repositories import MovieRepository, ClientRepository, RentalRepository


class MovieBinaryRepository(MovieRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file(self.__file_name)
        self.__load_data()

    def __create_file(self, file_name):
        try:
            with open(file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_data(self):
        try:
            with open(self.__file_name, 'rb') as file:
                for data in pickle.load(file):
                    movie = Movie(data.title, data.description, data.genre)
                    movie.id = data.id
                    super().add(movie)
        except Exception as exception:
            print(exception)

    def __save_to_file(self):
        with open(self.__file_name, 'wb') as file:
            pickle.dump(self.entities, file)

    def add(self, movie):
        movie_id = super().find_next_id()
        movie.id = movie_id
        super().add(movie)
        self.__save_to_file()

    def remove(self, movie_id):
        super().remove(movie_id)
        self.__save_to_file()

    def update_title(self, movie_id, title):
        super().update_title(movie_id, title)
        self.__save_to_file()

    def update_description(self, movie_id, description):
        super().update_description(movie_id, description)
        self.__save_to_file()

    def update_genre(self, movie_id, genre):
        super().update_genre(movie_id, genre)
        self.__save_to_file()


class ClientBinaryRepository(ClientRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file(self.__file_name)
        self.__load_data()

    def __create_file(self, file_name):
        try:
            with open(file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_data(self):
        try:
            with open(self.__file_name, 'rb') as file:
                for data in pickle.load(file):
                    client = Client(data.name)
                    client.id = data.id
                    super().add(client)
        except Exception as exception:
            print(exception)

    def __save_to_file(self):
        with open(self.__file_name, 'wb') as file:
            pickle.dump(self.entities, file)

    def add(self, client):
        client_id = super().find_next_id()
        client.id = client_id
        super().add(client)
        self.__save_to_file()

    def remove(self, client_id):
        super().remove(client_id)
        self.__save_to_file()

    def update_name(self, client_id, name):
        super().update_name(client_id, name)
        self.__save_to_file()


class RentalBinaryRepository(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file(self.__file_name)
        self.__load_data()

    def __create_file(self, file_name):
        try:
            with open(file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_data(self):
        try:
            with open(self.__file_name, 'rb') as file:
                for data in pickle.load(file):
                    rental = Rental(data.movie_id, data.client_id, data.rented_date, data.due_date, data.returned_date)
                    rental.id = data.id
                    super().add(rental)
        except Exception as exception:
            print(exception)

    def __save_to_file(self):
        with open(self.__file_name, 'wb') as file:
            pickle.dump(self.entities, file)

    def add(self, rental):
        rental_id = super().find_next_id()
        rental.id = rental_id
        super().add(rental)
        self.__save_to_file()

    def remove(self, rental_id):
        super().remove(rental_id)
        self.__save_to_file()

    def update_returned_date(self, rental_id, returned_date):
        super().update_returned_date(rental_id, returned_date)
        self.__save_to_file()
