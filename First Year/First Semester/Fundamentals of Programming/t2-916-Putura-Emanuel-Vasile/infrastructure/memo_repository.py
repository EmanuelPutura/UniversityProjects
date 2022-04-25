class RepositoryError(Exception):
    def __init__(self, error_message=''):
        self.__error_message = error_message

    def __str__(self):
        return self.__error_message


class Repository:
    def __init__(self, data=[]):
        self.__data = data

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, other):
        self.__data = other

    def add(self, entity):
        for element in self.__data:
            if element == entity:
                raise RepositoryError("RepositoryError: Element {} was already added to the repository.".format(str(element)))
        self.__data.append(entity)

    def find_element_index(self, entity):
        return self.__data.index(entity)

    def _search_by_id(self, id):
        """
            Returns the element in the repo having the given ID or None if no such element is found
        """
        for entity in self.__data:
            if entity.id == id:
                return entity
        return None

    def remove(self, id):
        """
            We assume each entity in the repository has an ID
        """
        entity = self._search_by_id(id)
        if entity is None:
            raise RepositoryError("No element with ID {} was found.".format(str(id)))
        self.__data.remove(entity)
        return entity

    def __len__(self):
        return len(self.__data)

    def __repr__(self):
        return str('Repository data: {}'.format(str(self.__data)))

    def __getitem__(self, key):
        return self.__data[key]
