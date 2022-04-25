class Iterator:
    """
    Abstract representation of an iterator
    """
    def __init__(self, collection):
        self.__colection = collection
        self.__position = 0

    def __next__(self):
        """
        Returns next element in collection
        :raises: StopIteration if there are no more elements
        """
        if self.__position == len(self.__colection.data):
            raise StopIteration()
        self.__position += 1
        return self.__colection.data[self.__position - 1]


class Collection:
    def __init__(self, data=[]):
        self.__data = data

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, other):
        self.__data = other

    def append(self, value):
        """
        Appends a value to the collection
        """
        self.__data.append(value)

    def __len__(self):
        """
        Returns the no of elements in the collection
        """
        return len(self.__data)

    def __iter__(self):
        """
        Returns an iterator for the collection
        """
        return Iterator(self)

    def __setitem__(self, key, value):
        """
        Sets the item from the given key to the given value
        """
        self.__data[key] = value

    def __getitem__(self, key):
        """
        Gets the item from a given key
        """
        return self.__data[key]

    def __delitem__(self, key):
        """
        Deletes an item from the collection
        """
        del self.__data[key]

    def __str__(self):
        """
        Returns the string representation of a collection. Uses __str__() method from <class 'list'>
        """
        return str(self.__data)
