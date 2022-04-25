from enum import Enum

from services.undo_redo_service import RedoManager, UndoManager


class UndoHandler:
    @staticmethod
    def add_movie_handler(movie_service, movie_id, rental_service):
        movie = movie_service.get_movie(movie_id)
        movie_service.remove_movie(movie_id)
        removed_rentals = rental_service.remove_movie_rentals(movie_id)
        RedoManager.register_operation(len(UndoManager.undo_operations()), movie_service, RedoHandlerEnum.ADD_MOVIE, movie, removed_rentals, rental_service)

    @staticmethod
    def add_client_handler(client_service, client_id, rental_service):
        client = client_service.get_client(client_id)
        client_service.remove_client(client_id)
        removed_rentals = rental_service.remove_client_rentals(client_id)
        RedoManager.register_operation(len(UndoManager.undo_operations()), client_service, RedoHandlerEnum.ADD_CLIENT, client, removed_rentals, rental_service)

    @staticmethod
    def rent_movie_handler(rental_service, rental_id):
        rental = rental_service.get_rental(rental_id)
        rental_service.remove_rental(rental_id)
        RedoManager.register_operation(len(UndoManager.undo_operations()), rental_service, RedoHandlerEnum.RENT_MOVIE, rental)

    @staticmethod
    def delete_movie_handler(movie_service, removed_movie, removed_rentals, rental_service):
        added_movie = movie_service.add_movie(removed_movie.title, removed_movie.description, removed_movie.genre)
        added_movie.id = removed_movie.id
        for rental in removed_rentals:
            restored_rental = rental_service.add_rental(rental.movie_id, rental.client_id, rental.rented_date, rental.due_date, rental.returned_date)
            restored_rental.id = rental.id
        RedoManager.register_operation(len(UndoManager.undo_operations()), movie_service, RedoHandlerEnum.REMOVE_MOVIE, removed_movie, removed_rentals, rental_service)

    @staticmethod
    def delete_client_handler(client_service, removed_client, removed_rentals, rental_service):
        added_client = client_service.add_client(removed_client.name)
        added_client.id = removed_client.id
        for rental in removed_rentals:
            restored_rental = rental_service.add_rental(rental.movie_id, rental.client_id, rental.rented_date, rental.due_date, rental.returned_date)
            restored_rental.id = rental.id
        RedoManager.register_operation(len(UndoManager.undo_operations()), client_service, RedoHandlerEnum.REMOVE_CLIENT, removed_client, removed_rentals, rental_service)

    @staticmethod
    def update_movie_title_handler(movie_service, movie_id, title):
        movie = movie_service.get_movie(movie_id)
        movie_title = movie.title
        movie_service.update_title(movie_id, title)
        RedoManager.register_operation(len(UndoManager.undo_operations()), movie_service, RedoHandlerEnum.UPDATE_MOVIE_TITLE,
                                       movie.id, movie_title)

    @staticmethod
    def update_movie_description_handler(movie_service, movie_id, description):
        movie = movie_service.get_movie(movie_id)
        movie_description = movie.description
        movie_service.update_description(movie_id, description)
        RedoManager.register_operation(len(UndoManager.undo_operations()), movie_service, RedoHandlerEnum.UPDATE_MOVIE_DESCRIPTION,
                                       movie.id, movie_description)

    @staticmethod
    def update_movie_genre_handler(movie_service, movie_id, genre):
        movie = movie_service.get_movie(movie_id)
        movie_genre = movie.genre
        movie_service.update_genre(movie_id, genre)
        RedoManager.register_operation(len(UndoManager.undo_operations()), movie_service, RedoHandlerEnum.UPDATE_MOVIE_GENRE,
                                       movie.id, movie_genre)

    @staticmethod
    def update_client_name_handler(client_service, client_id, name):
        client = client_service.get_client(client_id)
        client_name = client.name
        client_service.update_name(client_id, name)
        RedoManager.register_operation(len(UndoManager.undo_operations()), client_service, RedoHandlerEnum.UPDATE_CLIENT_NAME,
                                       client_id, client_name)

    @staticmethod
    def return_movie_handler(rental_service, rental_id):
        rental = rental_service.get_rental(rental_id)
        rental_returned_date = rental.returned_date
        rental_service.update_returned_date(rental_id, 'Not returned yet.')
        RedoManager.register_operation(len(UndoManager.undo_operations()), rental_service, RedoHandlerEnum.RETURN_MOVIE,
                                       rental_id, rental_returned_date)


class RedoHandler:
    @staticmethod
    def add_movie_handler(movie_service, movie, removed_rentals, rental_service):
        added_movie = movie_service.add_movie(movie.title, movie.description, movie.genre)
        added_movie.id = movie.id
        for rental in removed_rentals:
            added_rental = rental_service.add_rental(rental)
            added_rental.id = rental.id
        UndoManager.register_operation(movie_service, UndoHandlerEnum.ADD_MOVIE, movie.id, rental_service)

    @staticmethod
    def add_client_handler(client_service, client, removed_rentals, rental_service):
        added_client = client_service.add_client(client.name)
        added_client.id = client.id
        for rental in removed_rentals:
            added_rental = rental_service.add_rental(rental)
            added_rental.id = rental.id
        UndoManager.register_operation(client_service, UndoHandlerEnum.ADD_CLIENT, client.id, rental_service)

    @staticmethod
    def rent_movie_handler(rental_service, rental):
        added_rental = rental_service.add_rental(rental.movie_id, rental.client_id, rental.rented_date, rental.due_date, rental.returned_date)
        added_rental.id = rental.id
        UndoManager.register_operation(rental_service, UndoHandlerEnum.RENT_MOVIE, rental.id)

    @staticmethod
    def delete_movie_handler(movie_service, removed_movie, removed_rentals, rental_service):
        movie_service.remove_movie(removed_movie.id)
        rental_service.remove_movie_rentals(removed_movie.id)
        UndoManager.register_operation(movie_service, UndoHandlerEnum.REMOVE_MOVIE, removed_movie, removed_rentals, rental_service)

    @staticmethod
    def delete_client_handler(client_service, removed_client, removed_rentals, rental_service):
        client_service.remove_client(removed_client.id)
        rental_service.remove_client_rentals(removed_client.id)
        UndoManager.register_operation(client_service, UndoHandlerEnum.REMOVE_CLIENT, removed_client, removed_rentals, rental_service)

    @staticmethod
    def update_movie_title_handler(movie_service, movie_id, title):
        movie = movie_service.get_movie(movie_id)
        movie_title = movie.title
        movie_service.update_title(movie_id, title)
        UndoManager.register_operation(movie_service, UndoHandlerEnum.UPDATE_MOVIE_TITLE, movie_id, movie_title)

    @staticmethod
    def update_movie_description_handler(movie_service, movie_id, description):
        movie = movie_service.get_movie(movie_id)
        movie_description = movie.description
        movie_service.update_description(movie_id, description)
        UndoManager.register_operation(movie_service, UndoHandlerEnum.UPDATE_MOVIE_DESCRIPTION, movie_id, movie_description)

    @staticmethod
    def update_movie_genre_handler(movie_service, movie_id, genre):
        movie = movie_service.get_movie(movie_id)
        movie_genre = movie.genre
        movie_service.update_genre(movie_id, genre)
        UndoManager.register_operation(movie_service, UndoHandlerEnum.UPDATE_MOVIE_GENRE, movie_id, movie_genre)

    @staticmethod
    def update_client_name_handler(client_service, client_id, name):
        client = client_service.get_client(client_id)
        client_name = client.name
        client_service.update_name(client_id, name)
        UndoManager.register_operation(client_service, UndoHandlerEnum.UPDATE_CLIENT_NAME, client_id, client_name)

    @staticmethod
    def return_movie_handler(rental_service, rental_id, rental_returned_date):
        rental_service.update_returned_date(rental_id, rental_returned_date)
        UndoManager.register_operation(rental_service, UndoHandlerEnum.RETURN_MOVIE, rental_id)


class UndoHandlerEnum(Enum):
    ADD_MOVIE = UndoHandler.add_movie_handler
    REMOVE_MOVIE = UndoHandler.delete_movie_handler
    UPDATE_MOVIE_TITLE = UndoHandler.update_movie_title_handler
    UPDATE_MOVIE_DESCRIPTION = UndoHandler.update_movie_description_handler
    UPDATE_MOVIE_GENRE = UndoHandler.update_movie_genre_handler
    ADD_CLIENT = UndoHandler.add_client_handler
    REMOVE_CLIENT = UndoHandler.delete_client_handler
    UPDATE_CLIENT_NAME = UndoHandler.update_client_name_handler
    RENT_MOVIE = UndoHandler.rent_movie_handler
    RETURN_MOVIE = UndoHandler.return_movie_handler


class RedoHandlerEnum(Enum):
    ADD_MOVIE = RedoHandler.add_movie_handler
    REMOVE_MOVIE = RedoHandler.delete_movie_handler
    UPDATE_MOVIE_TITLE = RedoHandler.update_movie_title_handler
    UPDATE_MOVIE_DESCRIPTION = RedoHandler.update_movie_description_handler
    UPDATE_MOVIE_GENRE = RedoHandler.update_movie_genre_handler
    ADD_CLIENT = RedoHandler.add_client_handler
    REMOVE_CLIENT = RedoHandler.delete_client_handler
    UPDATE_CLIENT_NAME = RedoHandler.update_client_name_handler
    RENT_MOVIE = RedoHandler.rent_movie_handler
    RETURN_MOVIE = RedoHandler.return_movie_handler
