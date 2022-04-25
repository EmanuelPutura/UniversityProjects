from infrastructure.memory_repositories import MovieRepository, ClientRepository, RentalRepository


class MovieTextRepository(MovieRepository):
    def __init__(self, data_access_class, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file(self.__file_name)
        self.__data_access_class = data_access_class
        self.__load_data()

    def __create_file(self, file_name):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_data(self):
        with open(self.__file_name, 'r') as file:
            for line in file:
                movie = self.__data_access_class.read_from(line)
                super().add(movie)

    def add(self, movie):
        movie_id = super().find_next_id()
        movie.id = movie_id
        super().add(movie)
        self.__save_to_file(movie)

    def remove(self, movie_id):
        movie = super().remove(movie_id)
        movie_line = self.__data_access_class.get_line(movie)
        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(movie_line, '')
        with open(self.__file_name, 'w') as file:
            file.write(text)

    def __save_to_file(self, movie):
        with open(self.__file_name, 'a') as file:
            self.__data_access_class.write_to(file, movie)

    def update_title(self, movie_id, title):
        old_movie = self.find_by_id(movie_id)
        old_movie_line = self.__data_access_class.get_line(old_movie)
        new_movie = super().update_title(movie_id, title)
        new_movie_line = self.__data_access_class.get_line(new_movie)

        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(old_movie_line, new_movie_line)

        with open(self.__file_name, 'w') as file:
            file.write(text)

    def update_description(self, movie_id, description):
        old_movie = self.find_by_id(movie_id)
        old_movie_line = self.__data_access_class.get_line(old_movie)
        new_movie = super().update_description(movie_id, description)
        new_movie_line = self.__data_access_class.get_line(new_movie)

        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(old_movie_line, new_movie_line)

        with open(self.__file_name, 'w') as file:
            file.write(text)

    def update_genre(self, movie_id, genre):
        old_movie = self.find_by_id(movie_id)
        old_movie_line = self.__data_access_class.get_line(old_movie)
        new_movie = super().update_genre(movie_id, genre)
        new_movie_line = self.__data_access_class.get_line(new_movie)

        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(old_movie_line, new_movie_line)

        with open(self.__file_name, 'w') as file:
            file.write(text)


class ClientTextRepository(ClientRepository):
    def __init__(self, data_access_class, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file(self.__file_name)
        self.__data_access_class = data_access_class
        self.__load_data()

    def __create_file(self, file_name):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_data(self):
        with open(self.__file_name, 'rt') as file:
            for line in file:
                client = self.__data_access_class.read_from(line)
                super().add(client)

    def add(self, client):
        client_id = super().find_next_id()
        client.id = client_id
        super().add(client)
        self.__save_to_file(client)

    def remove(self, client_id):
        client = super().remove(client_id)
        client_line = self.__data_access_class.get_line(client)
        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(client_line, '')
        with open(self.__file_name, 'w') as file:
            file.write(text)

    def __save_to_file(self, client):
        with open(self.__file_name, 'a') as file:
            self.__data_access_class.write_to(file, client)

    def update_name(self, client_id, name):
        old_client = self.find_by_id(client_id)
        old_client_line = self.__data_access_class.get_line(old_client)
        new_client = super().update_name(client_id, name)
        new_client_line = self.__data_access_class.get_line(new_client)

        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(old_client_line, new_client_line)

        with open(self.__file_name, 'w') as file:
            file.write(text)


class RentalTextRepository(RentalRepository):
    def __init__(self, data_access_class, file_name):
        super().__init__()
        self.__file_name = file_name
        self.__create_file(self.__file_name)
        self.__data_access_class = data_access_class
        self.__load_data()

    def __create_file(self, file_name):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_data(self):
        with open(self.__file_name, 'rt') as file:
            for line in file:
                entity = self.__data_access_class.read_from(line)
                super().add(entity)

    def add(self, entity):
        entity_id = super().find_next_id()
        entity.id = entity_id
        super().add(entity)
        self.__save_to_file(entity)

    def remove(self, entity_id):
        entity = super().remove(entity_id)
        entity_line = self.__data_access_class.get_line(entity)
        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(entity_line, '')
        with open(self.__file_name, 'w') as file:
            file.write(text)

    def __save_to_file(self, entity):
        with open(self.__file_name, 'a') as file:
            self.__data_access_class.write_to(file, entity)

    def update_returned_date(self, rental_id, returned_date):
        old_rental = self.find_by_id(rental_id)
        old_rental_line = self.__data_access_class.get_line(old_rental)
        new_rental = super().update_returned_date(rental_id, returned_date)
        new_rental_line = self.__data_access_class.get_line(new_rental)

        with open(self.__file_name, 'r') as file:
            text = file.read()
            text = text.replace(old_rental_line, new_rental_line)

        with open(self.__file_name, 'w') as file:
            file.write(text)
