from erros.exceptions import RepositoryError


class Repository:
    """
    Represents an abstract data type for a generic repository
    """
    def __init__(self):
        self.__entities = []

    @property
    def entities(self):
        return self.__entities[:]

    @entities.setter
    def entities(self, other):
        self.__entities = other

    def add(self, entity):
        """
        Adds a new entity to the list
        :param entity: a new entity
        :return: -
        """
        for ent in self.__entities:
            if entity == ent:
                raise RepositoryError('{} was already added.\n'.format(entity))
        self.__entities.append(entity)

    def search_by_id(self, id):
        """
        Searches for entities having the given ID (or partially having it)
        :param id: a given ID
        :return: the list of found entities
        """
        items = []
        for entity in self.__entities:
            if str(id).lower() in str(entity.id).lower():
                items.append(entity)
        return items

    def find_by_id(self, entity_id):
        """
        Finds an entity by its ID
        :param entity_id: an entity ID
        :return: the entity if there is one with the given ID, None else
        """
        for entity in self.__entities:
            if entity.id == entity_id:
                return entity
        return None

    def find_next_id(self):
        ids = []
        for entity in self.__entities:
            ids.append(entity.id)
        id = 1
        while True:
            if id not in ids:
                return id
            id += 1

    def remove(self, entity_id):
        """
        Removes an entity by its ID
        :param entity_id: an entity ID
        :return: the removed entity
        """
        entity = self.find_by_id(entity_id)
        if entity is None:
            raise RepositoryError("'{}' is not a valid ID.\n".format(entity_id))
        self.__entities.remove(entity)
        return entity

    def __len__(self):
        """
        :return: the number of element in the entities list
        """
        return len(self.__entities)


class MovieRepository(Repository):
    """
    Represents an abstract data type for a movie repository
    """
    def update_title(self, movie_id, title):
        """
        Updates the title of a movie by its ID
        :param movie_id: a movie's ID
        :param title: a new title for the movie
        :return: the updated movie
        """
        movie = self.find_by_id(movie_id)
        if movie is None:
            raise RepositoryError("'{}' is not a valid ID.\n".format(movie_id))
        movie.title = title
        self.entities[self.entities.index(movie)] = movie
        return movie

    def update_description(self, movie_id, description):
        """
        Updates the description of a movie by its ID
        :param movie_id: a movie's ID
        :param description: a new description for the movie
        :return: the updated movie
        """
        movie = self.find_by_id(movie_id)
        if movie is None:
            raise RepositoryError("'{}' is not a valid ID.\n".format(movie_id))
        movie.description = description
        self.entities[self.entities.index(movie)] = movie
        return movie

    def update_genre(self, movie_id, genre):
        """
        Updates the genre of a movie by its ID
        :param movie_id: a movie's ID
        :param genre: a new genre for the movie
        :return: the updated movie
        """
        movie = self.find_by_id(movie_id)
        if movie is None:
            raise RepositoryError("'{}' is not a valid ID.\n".format(movie_id))
        movie.genre = genre
        self.entities[self.entities.index(movie)] = movie
        return movie

    def search_by_title(self, title):
        """
        Searches movies by a given title
        :param title: a given title
        :return: the list of found movies
        """
        items = []
        for movie in self.entities:
            if title.lower() in movie.title.lower():
                items.append(movie)
        return items

    def search_by_description(self, description):
        """
        Searches movies by a given description
        :param description: a given description
        :return: the list of found movies
        """
        items = []
        for movie in self.entities:
            if description.lower() in movie.description.lower():
                items.append(movie)
        return items

    def search_by_genre(self, genre):
        """
        Searches movies by a given genre
        :param genre: a given genre
        :return: the list of found movies
        """
        items = []
        for movie in self.entities:
            if genre.lower() in movie.genre.lower():
                items.append(movie)
        return items


class ClientRepository(Repository):
    """
    Represents an abstract data type for a client repository
    """
    def update_name(self, client_id, name):
        """
        Updates the name of a client by its ID
        :param client_id: a client's ID
        :param name: a new name for the client
        :return: the updated client
        """
        client = self.find_by_id(client_id)
        if client is None:
            raise RepositoryError("'{}' is not a valid ID.\n".format(client_id))
        client.name = name
        self.entities[self.entities.index(client)] = client
        return client

    def search_by_name(self, name):
        """
        Searches clients by a given name
        :param name: a given name
        :return: the list of found clients
        """
        items = []
        for client in self.entities:
            if name.lower() in client.name.lower():
                items.append(client)
        return items


class RentalRepository(Repository):
    """
    Represents an abstract data type for a rental repository
    """
    def update_returned_date(self, rental_id, returned_date):
        """
        Updates a rental's returned date
        :param rental_id: a rental's ID
        :param returned_date: a new returned date
        :return: the updated rental
        """
        rental = self.find_by_id(rental_id)
        if rental is None:
            raise RepositoryError("'{}' is not a valid ID.\n".format(rental))
        if not isinstance(returned_date, str) and rental.rented_date > returned_date:
            raise RepositoryError("'{}' is not a valid returned date.\n".format(returned_date))
        rental.returned_date = returned_date
        self.entities[self.entities.index(rental)] = rental
        return rental
