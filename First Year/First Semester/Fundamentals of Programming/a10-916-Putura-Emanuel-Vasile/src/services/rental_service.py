from domain.rental import Rental
from datetime import date

from erros.exceptions import ServiceError
from iterators.collection import comb_sort
from services.client_rental_dto import ClientRentalAssembler
from services.movie_delay_dto import MovieDelayAssembler
from services.movie_rental_dto import MovieRentalAssembler


class RentalService:
    """
    Service class for the Rental class
    """
    def __init__(self, rental_validator, rental_repository, movie_repository, client_repository):
        self.__rental_validator = rental_validator
        self.__rental_repository = rental_repository
        self.__movie_repository = movie_repository
        self.__client_repository = client_repository

    def add_rental(self, movie_id, client_id, rented_date, due_date, returned_date='Not returned yet.'):
        """
        Adds a new rental
        :param movie_id: the rental's movie ID
        :param client_id: the rental's client ID
        :param rented_date: the rental's rented date
        :param due_date: the rental's due date
        :param returned_date: the rental's returned date
        :return: the added rental
        """
        rental = Rental(movie_id, client_id, rented_date, due_date, returned_date)
        self.__rental_validator.validate(rental)
        self.check_rentals_with_movie_id(rental)
        self.check_client_returned_dates(rental)
        self.__rental_repository.add(rental)
        return rental

    def remove_rental(self, rental_id):
        self.__rental_repository.remove(rental_id)

    def remove_movie_rentals(self, movie_id):
        removed_rentals = []
        rentals = self.get_all_rentals()
        for rental in rentals:
            if rental.movie_id == movie_id:
                removed_rentals.append(rental)
                self.__rental_repository.remove(rental.id)
        return removed_rentals

    def remove_client_rentals(self, client_id):
        removed_rentals = []
        rentals = self.get_all_rentals()
        for rental in rentals:
            if rental.client_id == client_id:
                removed_rentals.append(rental)
                self.__rental_repository.remove(rental.id)
        return removed_rentals

    def update_returned_date(self, rental_id, returned_date):
        """
        Updates a rental's returned date, being given its ID
        :param rental_id: the rental's ID
        :param returned_date: the rental's returned date
        :return: -
        """
        self.__rental_repository.update_returned_date(rental_id, returned_date)

    def find_movies_rented_days(self):
        """
        Finds the corresponding MovieRentalDTO objects
        :return: the list of corresponding MovieRentalDTO objects
        """
        movie_dtos = []
        movies = self.__movie_repository.entities
        for movie in movies:
            movie_dto = MovieRentalAssembler.create_dto(movie, self.count_movie_rental_days(movie.id))
            movie_dtos.append(movie_dto)
        return movie_dtos

    def find_clients_movie_rental_days(self):
        """
        Finds the corresponding ClientRentalDTO objects
        :return: the list of corresponding ClientRentalDTO objects
        """
        clients_dtos = []
        clients = self.__client_repository.entities
        for client in clients:
            client_dto = ClientRentalAssembler.create_dto(client, self.count_client_movie_rental_days(client.id))
            clients_dtos.append(client_dto)
        return clients_dtos

    def find_rentals_with_passed_due_date(self):
        """
        Finds the current rentals with passed due date
        :return: the current list of rentals with passed due date
        """
        rentals = self.get_all_rentals()
        passed_rentals = []
        for rental in rentals:
            if not isinstance(rental.returned_date, str) and \
                    rental.returned_date > rental.due_date:
                passed_rentals.append(rental)
            elif isinstance(rental.returned_date, str) and date.today() > rental.due_date:
                passed_rentals.append(rental)
        return passed_rentals

    def find_current_late_rentals(self):
        """
        Finds the corresponding MovieDelayDTO objects for the current late rentals
        :return: the list of corresponding MovieDelayDTO objects for the current late rentals
        """
        movie_dtos = []
        movies = self.__movie_repository.entities
        passed_rentals = self.find_rentals_with_passed_due_date()
        for movie in movies:
            delay = self.count_movie_passed_rental_delay_days(passed_rentals, movie.id)
            if delay > 0:
                movie_dto = MovieDelayAssembler.create_dto(movie, delay)
                movie_dtos.append(movie_dto)
        return movie_dtos

    def find_most_rented_movies(self):
        """
        Sorts the list of the corresponding MovieRentalDTO objects by the number of rented days
        :return: the sorted list of the corresponding MovieRentalDTO objects by the number of rented days
        """
        movie_dtos = self.find_movies_rented_days()
        # movie_dtos.sort(key=lambda dto: dto.number_of_rented_days, reverse=True)
        movie_dtos = comb_sort(movie_dtos, lambda dto1, dto2: dto1.number_of_rented_days > dto2.number_of_rented_days)
        return movie_dtos

    def find_most_active_clients(self):
        """
        Sorts the list of the corresponding ClientRentalDTO objects by the total number of movie rental days they have
        :return: the sorted list of the corresponding ClientRentalDTO objects by the total number of movie rental days they have
        """
        client_dtos = self.find_clients_movie_rental_days()
        # client_dtos.sort(key=lambda dto: dto.rental_days_number, reverse=True)
        client_dtos = comb_sort(client_dtos, lambda dto1, dto2: dto1.rental_days_number > dto2.rental_days_number)
        return client_dtos

    def find_late_rentals(self):
        """
        Sorts the list of the corresponding MovieDelayDTO objects by the number of days of delay
        :return: the list of the corresponding MovieDelayDTO objects by the number of days of delay
        """
        movie_dtos = self.find_current_late_rentals()
        # movie_dtos.sort(key=lambda dto: dto.delay, reverse=True)
        movie_dtos = comb_sort(movie_dtos, lambda dto1, dto2: dto1.delay > dto2.delay)
        return movie_dtos

    def count_movie_rental_days(self, movie_id):
        """
        Counts the number of rental days for the movie corresponding to a given ID
        :param movie_id: a given movie ID
        :return: the number of rental days for the movie corresponding to the given ID
        """
        number_of_rental_days = 0
        rentals = self.get_all_rentals()
        for rental in rentals:
            if rental.movie_id == movie_id:
                number_of_rental_days = self.find_number_of_rental_days(number_of_rental_days, rental)
        return number_of_rental_days

    def count_client_movie_rental_days(self, client_id):
        """
        Counts the number of movie rental days for the client corresponding to a given ID
        :param client_id: a given client ID
        :return: the number of movie rental days for the client corresponding to a given ID
        """
        number_of_rental_days = 0
        rentals = self.get_all_rentals()
        for rental in rentals:
            if rental.client_id == client_id:
                number_of_rental_days = self.find_number_of_rental_days(number_of_rental_days, rental)
        return number_of_rental_days

    def count_movie_passed_rental_delay_days(self, passed_rentals, movie_id):
        """
        Counts the days of delay for a given movie, considering all the current late rentals
        :param passed_rentals: the list of the current passed rentals
        :param movie_id: a given movie ID
        :return: the days of delay for a given movie, considering all the current late rentals
        """
        number_of_passed_days = 0
        for passed_rental in passed_rentals:
            if passed_rental.movie_id == movie_id:
                if not isinstance(passed_rental.returned_date, str):
                    number_of_passed_days += (passed_rental.returned_date - passed_rental.due_date).days
                else:
                    number_of_passed_days += (date.today() - passed_rental.due_date).days
        return number_of_passed_days

    def find_number_of_rental_days(self, number_of_rental_days, rental):
        """
        Finds the number of rental days for a rental
        :param number_of_rental_days: the number of rental days so far
        :param rental: a given rental
        :return: the number of rental days for a rental
        """
        if not isinstance(rental.returned_date, str):
            number_of_rental_days += (rental.returned_date - rental.rented_date).days
        else:
            # the movie has not been returned yet
            number_of_rental_days += (date.today() - rental.rented_date).days
        return number_of_rental_days

    def get_all_rentals(self):
        """
        Gets all the existing rentals
        :return: all the existing rentals
        """
        return self.__rental_repository.entities

    def get_rental(self, rental_id):
        return self.__rental_repository.find_by_id(rental_id)

    def find_and_update_rental(self, client_id, movie_id, returned_date):
        """
        Gets a rental, being given some of its attributes, and updates its returned date
        :param client_id: the rental's client ID
        :param movie_id: the rental's movie ID
        :param returned_date: the rental's new returned date
        :return: the rental's ID
        """
        rental_id = self.check_rental_existence(client_id, movie_id)
        self.update_returned_date(rental_id, returned_date)
        return rental_id

    def check_rentals_with_movie_id(self, rental):
        """
        Checks if during the same period there are rentals with the same movie ID as a given rental
        :param rental: a given rental
        :return: -
        ":exception ServiceError: if during the same period there are rentals with the same movie ID as a given rental
        """
        rentals = self.get_all_rentals()
        for r in rentals:
            if r.movie_id == rental.movie_id:
                if not isinstance(r.returned_date, str) and not (r.returned_date < rental.rented_date or r.rented_date > rental.due_date):
                    raise ServiceError("The movie '{}' was already rented.\n".format(rental.movie_id))
                elif isinstance(r.returned_date, str) and rental.due_date > r.rented_date:
                    raise ServiceError("The movie '{}' was already rented.\n".format(rental.movie_id))

    def check_client_returned_dates(self, rental):
        """
        Checks a returned date
        :param rental: a rental
        :return: an error message if the returned date is not OK, '' else
        """
        number_of_errors = 0
        for r in self.__rental_repository.entities:
            if r.client_id == rental.client_id:
                if rental.rented_date > r.due_date and isinstance(r.returned_date, str) or \
                        not isinstance(r.returned_date, str) and r.due_date < r.returned_date or \
                        isinstance(r.returned_date, str) and r.due_date < date.today():
                    number_of_errors += 1
        if number_of_errors > 0:
            raise ServiceError("Client '{}' has {} rentals that were not returned in time.\n".format(rental.client_id,
                                                                                        number_of_errors))

    def check_rental_existence(self, client_id, movie_id):
        """
        Checks if there is a rental with the given IDs and if there is one its ID is returned
        :param client_id: a client's ID
        :param movie_id: a movie's ID
        :return: the ID of the found rental (if it exists)
        """
        for rental in self.__rental_repository.entities:
            if rental.client_id == client_id and rental.movie_id == movie_id and isinstance(rental.returned_date, str):
                return rental.id
        raise ServiceError("There is no active rental with client ID '{}' and movie ID '{}'.\n".format(client_id, movie_id))
