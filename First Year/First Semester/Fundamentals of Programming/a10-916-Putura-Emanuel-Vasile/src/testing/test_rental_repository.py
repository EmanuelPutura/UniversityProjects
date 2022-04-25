import unittest
import datetime

from domain.rental import Rental
from erros.exceptions import RepositoryError
from infrastructure.memory_repositories import RentalRepository


class TestRentalRepository(unittest.TestCase):
    def test_update_returned_date(self):
        repository = RentalRepository()
        Rental.clear_number_of_instances()
        repository.add(Rental(1, 1, datetime.date(2020, 2, 28), datetime.date(2020, 7, 1)))
        repository.update_returned_date(1, datetime.date(2020, 6, 26))
        self.assertEqual(repository.entities[0].returned_date, datetime.date(2020, 6, 26))
        self.assertRaises(RepositoryError, repository.update_returned_date, 2, datetime.date(2020, 6, 26))
        self.assertRaises(RepositoryError, repository.update_returned_date, 1, datetime.date(2019, 2, 28))
