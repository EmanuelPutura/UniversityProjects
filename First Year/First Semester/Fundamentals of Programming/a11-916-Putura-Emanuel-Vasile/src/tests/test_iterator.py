import unittest

from iterator.collection import Collection


class TestIterator(unittest.TestCase):
    def setUp(self):
        self.__colection = Collection()

    def test_collection_append(self):
        for i in range(5):
            self.__colection.append(i)
        for i in range(5):
            self.assertEqual(self.__colection[i], i)

    def test_collection_data(self):
        for no in self.__colection.data:
            self.assertEqual(no in self.__colection, True)
        self.__colection.data = [5, 6, 7]
        for no in self.__colection:
            self.assertEqual(no in [5, 6, 7], True)

    def test_collection_len(self):
        self.__colection.data = [5, 6, 7]
        self.assertEqual(len(self.__colection), 3)

    def test_collection_del(self):
        self.__colection.data = [5, 6, 7]
        del self.__colection[2]
        self.assertEqual(len(self.__colection), 2)
        self.assertEqual(self.__colection[0], 5)
        self.assertEqual(self.__colection[1], 6)

    def test_collection_str(self):
        self.__colection.data = [5, 6, 7]
        self.assertEqual(str(self.__colection), '[5, 6, 7]')
