import sqlite3

from erros.exceptions import RepositoryError
from infrastructure.memory_repositories import MovieRepository, ClientRepository, RentalRepository
from sqlite3 import Error


class DatabaseService:
    @staticmethod
    def create_connection(path):
        connection = None
        try:
            connection = sqlite3.connect(path)
        except Error as error:
            raise RepositoryError("Database connection error occurred: '{}'\n".format(str(error)))
        return connection

    @staticmethod
    def execute_query(connection, query):
        cursor = connection.cursor()
        try:
            cursor.execute(query)
            connection.commit()
        except Error as error:
            raise RepositoryError("Database query execution error occurred: '{}'\n".format(str(error)))

    @staticmethod
    def execute_read_query(connection, query):
        cursor = connection.cursor()
        result = None
        try:
            cursor.execute(query)
            result = cursor.fetchall()
        except Error as error:
            raise RepositoryError("Database query execution error occurred: '{}'\n".format(str(error)))
        return result


class MovieDatabaseRepository(MovieRepository):
    def __init__(self, data_access_class, database_path):
        super().__init__()
        self.__data_access_class = data_access_class
        self.__db_connection = DatabaseService.create_connection(database_path)
        self.__create_table()
        self.__load_data()

    def __create_table(self):
        create_movies_table = """
            CREATE TABLE IF NOT EXISTS movies (
            id INTEGER PRIMARY KEY,
            title TEXT NOT NULL,
            description TEXT NOT NULL,
            genre TEXT NOT NULL
            );
        """
        DatabaseService.execute_query(self.__db_connection, create_movies_table)

    def __load_data(self):
        select_movies_query = "SELECT * FROM movies"
        movie_lines = DatabaseService.execute_read_query(self.__db_connection, select_movies_query)
        for line in movie_lines:
            movie = self.__data_access_class.get_entity_from_db_line(str(line))
            super().add(movie)

    def add(self, movie):
        movie.id = super().find_next_id()
        super().add(movie)
        insert_movie_query = """
            INSERT INTO 
                movies (id, title, description, genre)
            VALUES\n\t
        """
        insert_movie_query += self.__data_access_class.get_db_line(movie)
        DatabaseService.execute_query(self.__db_connection, insert_movie_query)

    def remove(self, movie_id):
        movie = super().remove(movie_id)
        delete_movie_query = """
            DELETE FROM movies WHERE id = 
        """
        delete_movie_query += str(movie.id)
        DatabaseService.execute_query(self.__db_connection, delete_movie_query)

    def update_title(self, movie_id, title):
        super().update_title(movie_id, title)
        update_title_query = """
            UPDATE
                movies
            SET
                title = "{}"
            WHERE
                id = {}
        """.format(title, str(movie_id))
        DatabaseService.execute_query(self.__db_connection, update_title_query)

    def update_description(self, movie_id, description):
        super().update_description(movie_id, description)
        update_description_query = """
            UPDATE
                movies
            SET
                description = "{}"
            WHERE
                id = {}
        """.format(description, str(movie_id))
        DatabaseService.execute_query(self.__db_connection, update_description_query)

    def update_genre(self, movie_id, genre):
        super().update_genre(movie_id, genre)
        update_genre_query = """
            UPDATE
                movies
            SET
                genre = "{}"
            WHERE
                id = {}
        """.format(genre, str(movie_id))
        DatabaseService.execute_query(self.__db_connection, update_genre_query)


class ClientDatabaseRepository(ClientRepository):
    def __init__(self, data_access_class, database_path):
        super().__init__()
        self.__data_access_class = data_access_class
        self.__db_connection = DatabaseService.create_connection(database_path)
        self.__create_table()
        self.__load_data()

    def __create_table(self):
        create_clients_table = """
            CREATE TABLE IF NOT EXISTS clients (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL
            );
        """
        DatabaseService.execute_query(self.__db_connection, create_clients_table)

    def __load_data(self):
        select_clients_query = "SELECT * FROM clients"
        client_lines = DatabaseService.execute_read_query(self.__db_connection, select_clients_query)
        for line in client_lines:
            client = self.__data_access_class.get_entity_from_db_line(str(line))
            super().add(client)

    def add(self, client):
        client.id = super().find_next_id()
        super().add(client)
        insert_client_query = """
            INSERT INTO 
                clients (id, name)
            VALUES\n\t
        """
        insert_client_query += self.__data_access_class.get_db_line(client)
        DatabaseService.execute_query(self.__db_connection, insert_client_query)

    def remove(self, client_id):
        client = super().remove(client_id)
        delete_client_query = """
            DELETE FROM clients WHERE id = 
        """
        delete_client_query += str(client.id)
        DatabaseService.execute_query(self.__db_connection, delete_client_query)

    def update_name(self, client_id, name):
        super().update_name(client_id, name)
        update_name_query = """
            UPDATE
                clients
            SET
                name = "{}"
            WHERE
                id = {}
        """.format(name, str(client_id))
        DatabaseService.execute_query(self.__db_connection, update_name_query)


class RentalDatabaseRepository(RentalRepository):
    def __init__(self, data_access_class, database_path):
        super().__init__()
        self.__data_access_class = data_access_class
        self.__db_connection = DatabaseService.create_connection(database_path)
        self.__create_table()
        self.__load_data()

    def __create_table(self):
        create_rentals_table = """
            CREATE TABLE IF NOT EXISTS rentals (
            id INTEGER PRIMARY KEY,
            movie_id INTEGER NOT NULL,
            client_id INTEGER NOT NULL,
            rented_date TEXT NOT NULL,
            due_date TEXT NOT NULL,
            returned_date TEXT NOT NULL
            );
        """
        DatabaseService.execute_query(self.__db_connection, create_rentals_table)

    def __load_data(self):
        select_rentals_query = "SELECT * FROM rentals"
        rental_lines = DatabaseService.execute_read_query(self.__db_connection, select_rentals_query)
        for line in rental_lines:
            rental = self.__data_access_class.get_entity_from_db_line(str(line))
            super().add(rental)

    def add(self, rental):
        rental.id = super().find_next_id()
        super().add(rental)
        insert_rental_query = """
            INSERT INTO 
                rentals (id, movie_id, client_id, rented_date, due_date, returned_date)
            VALUES\n\t
        """
        insert_rental_query += self.__data_access_class.get_db_line(rental)
        DatabaseService.execute_query(self.__db_connection, insert_rental_query)

    def remove(self, rental_id):
        rental = super().remove(rental_id)
        delete_rental_query = """
            DELETE FROM rentals WHERE id = 
        """
        delete_rental_query += str(rental.id)
        DatabaseService.execute_query(self.__db_connection, delete_rental_query)

    def update_returned_date(self, rental_id, returned_date):
        super().update_returned_date(rental_id, returned_date)
        update_returned_date_query = """
            UPDATE
                rentals
            SET
                returned_date = "{}"
            WHERE 
                id = {}
        """.format(returned_date, rental_id)
        DatabaseService.execute_query(self.__db_connection, update_returned_date_query)
