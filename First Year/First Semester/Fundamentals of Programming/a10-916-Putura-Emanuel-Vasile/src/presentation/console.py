from colors.color import Color
from erros.exceptions import ValidationError, RepositoryError, IDError, ServiceError, UndoRedoError
import datetime

from services.undo_redo_handlers import UndoHandlerEnum
from services.undo_redo_service import UndoManager, RedoManager


class Console:
    def __init__(self, movie_service, client_service, rental_service):
        self.__movie_service = movie_service
        self.__client_service = client_service
        self.__rental_service = rental_service
        self.__commands = {'am': self.ui_add_movie, 'ac': self.ui_add_client, 'rm': self.ui_remove_movie, 'rc': self.ui_remove_client,
                           'um': self.ui_update_movie, 'uc': self.ui_update_client, 'lm': self.ui_list_movies, 'lc': self.ui_list_clients,
                           'rem': self.ui_rent_movie, 'rtm': self.ui_return_movie, 'sm': self.ui_search_movies, 'sc': self.ui_search_clients,
                           'statm': self.ui_most_rented_movies_statistics, 'statc': self.ui_most_active_clients_statistics,
                           'statr': self.ui_late_rentals_statistics, 'undo': self.ui_undo, 'redo': self.ui_redo}

    def ui_add_movie(self):
        title = input(Color.OKGREEN + 'Please input movie title: ' + Color.ENDC)
        description = input(Color.OKGREEN + 'Please input movie description: ' + Color.ENDC)
        genre = input(Color.OKGREEN + 'Please input movie genre: ' + Color.ENDC)
        added_movie = self.__movie_service.add_movie(title, description, genre)
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.ADD_MOVIE, added_movie.id, self.__rental_service)

    def ui_add_client(self):
        name = input(Color.OKGREEN + 'Please input client name: ' + Color.ENDC)
        added_client = self.__client_service.add_client(name)
        UndoManager.register_operation(self.__client_service, UndoHandlerEnum.ADD_CLIENT, added_client.id, self.__rental_service)

    def ui_remove_movie(self):
        movie_id = input(Color.OKGREEN + 'Please input movie ID: ' + Color.ENDC)
        if not movie_id.isdigit():
            raise IDError("'{}' is not a valid ID.\n".format(movie_id))
        removed_movie = self.__movie_service.get_movie(int(movie_id))
        self.__movie_service.remove_movie(int(movie_id))
        removed_rentals = self.__rental_service.remove_movie_rentals(int(movie_id))
        UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.REMOVE_MOVIE, removed_movie, removed_rentals, self.__rental_service)

    def ui_remove_client(self):
        client_id = input(Color.OKGREEN + 'Please input client ID: ' + Color.ENDC)
        if not client_id.isdigit():
            raise IDError("'{}' is not a valid ID.\n".format(client_id))
        removed_client = self.__client_service.get_client(int(client_id))
        self.__client_service.remove_client(int(client_id))
        removed_rentals = self.__rental_service.remove_client_rentals(int(client_id))
        UndoManager.register_operation(self.__client_service, UndoHandlerEnum.REMOVE_CLIENT, removed_client, removed_rentals, self.__rental_service)

    def ui_update_movie(self):
        commands = {'t': self.__movie_service.update_title, 'd': self.__movie_service.update_description,
                    'g': self.__movie_service.update_genre}
        handlers = {'t': UndoHandlerEnum.UPDATE_MOVIE_TITLE, 'd': UndoHandlerEnum.UPDATE_MOVIE_DESCRIPTION,
                    'g': UndoHandlerEnum.UPDATE_MOVIE_GENRE}
        messages = {'t': Color.OKGREEN + 'Please input a new movie title: ' + Color.ENDC, 'd': Color.OKGREEN + 'Please input a new movie description: ' + Color.ENDC,
                    'g': Color.OKGREEN + 'Please input a new movie genre: ' + Color.ENDC}

        print(Color.OKGREEN + ' t - Update movie title\n d - Update movie description\n g - Update movie genre' + Color.ENDC)
        command = input('>> ').strip()
        if command in commands:
            movie_id = input(Color.OKGREEN + "Please input movie's ID: " + Color.ENDC)
            if not movie_id.isdigit():
                raise IDError("'{}' is not a valid ID.\n".format(movie_id))
            new_data = input(messages[command])

            movie = self.__movie_service.get_movie(int(movie_id))
            data = {'t': movie.title, 'd': movie.description, 'g': movie.genre}
            UndoManager.register_operation(self.__movie_service, handlers[command], movie.id, data[command])

            commands[command](int(movie_id), new_data)
        else:
            print(Color.FAIL + 'Invalid command.\n' + Color.ENDC)

    def ui_update_client(self):
        client_id = input(Color.OKGREEN + "Please input client's ID: " + Color.ENDC)
        if not client_id.isdigit():
            raise IDError("'{}' is not a valid ID.\n".format(client_id))
        name = input(Color.OKGREEN + "Please input the client's name: " + Color.ENDC)
        client = self.__client_service.get_client(int(client_id))
        UndoManager.register_operation(self.__client_service, UndoHandlerEnum.UPDATE_CLIENT_NAME, client.id, client.name)
        self.__client_service.update_name(int(client_id), name)

    def ui_list_movies(self):
        movies = self.__movie_service.get_all_movies()
        if not len(movies):
            print(Color.FAIL + 'There are no movies.\n' + Color.ENDC)
            return
        for movie in movies:
            print(movie)
        print()

    def ui_list_clients(self):
        clients = self.__client_service.get_all_clients()
        if not len(clients):
            print(Color.FAIL + 'There are no clients.\n' + Color.ENDC)
            return
        for client in clients:
            print(client)
        print()

    def ui_rent_movie(self):
        client_id = input(Color.OKGREEN + "Please input client's ID: ")
        movie_id = input("Please input movie's ID: ")
        rented_date = input("Please input the starting date of the rental, in the format 'day/month/year': ")
        due_date = input("Please input the due date of the rental, in the format 'day/month/year': " + Color.ENDC)

        if not movie_id.isdigit() or self.__movie_service.get_movie(int(movie_id)) is None:
            raise IDError("'{}' is not a valid ID.\n".format(movie_id))
        if not client_id.isdigit() or self.__client_service.get_client(int(client_id)) is None:
            raise IDError("'{}' is not a valid ID.\n".format(client_id))

        try:
            rented_date = datetime.datetime.strptime(rented_date, '%d/%m/%Y').date()
            due_date = datetime.datetime.strptime(due_date, '%d/%m/%Y').date()
            added_rental = self.__rental_service.add_rental(int(movie_id), int(client_id), rented_date, due_date)
            UndoManager.register_operation(self.__rental_service, UndoHandlerEnum.RENT_MOVIE, added_rental.id)
        except RepositoryError as repositoryError:
            print(repositoryError)
        except ServiceError as serviceError:
            print(serviceError)
        except IDError as idError:
            print(idError)
        except ValidationError as validationError:
            print(validationError)
        except Exception:
            print(Color.FAIL + 'Invalid rented or due dates.\n' + Color.ENDC)

    def ui_return_movie(self):
        client_id = input(Color.OKGREEN + "Please input client's ID: ")
        movie_id = input("Please input movie's ID: ")
        returned_date = input("Please input the return date, in the format 'day/month/year': ")

        if not movie_id.isdigit() or self.__movie_service.get_movie(int(movie_id)) is None:
            raise IDError("'{}' is not a valid ID.\n".format(movie_id))
        if not client_id.isdigit() or self.__client_service.get_client(int(client_id)) is None:
            raise IDError("'{}' is not a valid ID.\n".format(client_id))

        try:
            returned_date = datetime.datetime.strptime(returned_date, '%d/%m/%Y').date()
            rental_id = self.__rental_service.find_and_update_rental(int(client_id), int(movie_id), returned_date)
            UndoManager.register_operation(self.__rental_service, UndoHandlerEnum.RETURN_MOVIE, rental_id)
        except RepositoryError as repositoryError:
            print(repositoryError)
        except ServiceError as serviceError:
            print(serviceError)
        except IDError as idError:
            print(idError)
        except ValidationError as validationError:
            print(validationError)
        except Exception:
            print(Color.FAIL + 'Invalid return date.\n' + Color.ENDC)

    def ui_search_movies(self):
        print(Color.OKGREEN + 'Select search criteria: ' + Color.ENDC)
        commands = {'si': self.__movie_service.search_by_id, 'st': self.__movie_service.search_by_title,
                    'sd': self.__movie_service.search_by_description, 'sg': self.__movie_service.search_by_genre}
        messages = {'si': Color.OKGREEN + 'Please input a movie ID: ' + Color.ENDC, 'st': Color.OKGREEN +
                    'Please input a movie title: ' + Color.ENDC, 'sd': Color.OKGREEN + 'Please input a movie description: ' + Color.ENDC,
                    'sg': Color.OKGREEN + 'Please input a movie genre: ' + Color.ENDC}
        print(Color.OKGREEN + ' si - Search by movie ID\n st - Search by movie title\n sd - Search by movie description\n sg - Search by movie genre' + Color.ENDC)
        none_message = 'No movies found.\n'
        command = input('>> ').strip()
        self.perform_search(command, commands, messages, none_message)

    def perform_search(self, command, commands, messages, none_message):
        if command in commands:
            item = input(messages[command])
            entities = commands[command](item)
            if not len(entities):
                print(Color.FAIL + none_message + Color.ENDC)
            else:
                self.print_entities(entities)
        else:
            print(Color.FAIL + 'Invalid command.\n' + Color.ENDC)

    def ui_search_clients(self):
        print(Color.OKGREEN + 'Select search criteria: ' + Color.ENDC)
        commands = {'si': self.__client_service.search_by_id, 'sn': self.__client_service.search_by_name}
        messages = {'si': Color.OKGREEN + 'Please input client ID: ' + Color.ENDC,
                    'sn': Color.OKGREEN + 'Please input client name: ' + Color.ENDC}
        print(Color.OKGREEN + ' si - Search by client ID\n sn - Search by client name' + Color.ENDC)
        none_message = 'No clients found.\n'
        command = input('>> ').strip()
        self.perform_search(command, commands, messages, none_message)

    def ui_most_rented_movies_statistics(self):
        movie_dtos = self.__rental_service.find_most_rented_movies()
        self.print_entities(movie_dtos)

    def ui_most_active_clients_statistics(self):
        client_dtos = self.__rental_service.find_most_active_clients()
        self.print_entities(client_dtos)

    def ui_late_rentals_statistics(self):
        movie_dtos = self.__rental_service.find_late_rentals()
        self.print_entities(movie_dtos)

    def ui_undo(self):
        UndoManager.undo()

    def ui_redo(self):
        RedoManager.redo()

    def print_entities(self, entities):
        print()
        if not len(entities):
            print(Color.FAIL + 'No entities found.\n' + Color.ENDC)
            return
        for entity in entities:
            print(entity)

    @staticmethod
    def print_menu():
        print(Color.OKCYAN + '******** Movie Rental Application ********')
        print(Color.OKBLUE + ' am - Add movie\n ac - Add client\n rm - Remove movie\n rc - Remove client')
        print(' um - Update movie\n uc - Update client\n lm - List movies\n lc - List clients')
        print(' rem - Rent movie\n rtm - Return movie\n sm - Search movies\n sc - Search clients')
        print(' statm - Provides statistics regarding the most rented movies')
        print(' statc - Provides statistics regarding the most active clients')
        print(' statr - Provides statistics regarding the late rentals')
        print(' undo - Undo last operation\n redo - Redo last undo operation')
        print(' exit - Exit')
        print(Color.OKCYAN + '******************************************\n' + Color.ENDC)

    def run(self):
        # self.ui_test_values()
        while True:
            self.print_menu()
            command = input('>> ').strip()
            if command == 'exit':
                return
            if command in self.__commands:
                try:
                    self.__commands[command]()
                except IDError as idError:
                    print(idError)
                except ValidationError as validationError:
                    print(validationError)
                except RepositoryError as repositoryError:
                    print(repositoryError)
                except ServiceError as serviceError:
                    print(serviceError)
                except UndoRedoError as undoRedoError:
                    print(undoRedoError)
                except Exception as exception:
                    print(Color.FAIL + 'Unexpected exception occurred:\n' + str(exception) + '\n' + Color.ENDC)
            else:
                print(Color.FAIL + 'Invalid command.\n' + Color.ENDC)

    def ui_test_values(self):
        self.__rental_service.add_rental(1, 1, datetime.date(2020, 11, 22), datetime.date(2020, 11, 30),
                                         datetime.date(2020, 12, 1))
        self.__rental_service.add_rental(2, 2, datetime.date(2020, 11, 27), datetime.date(2021, 1, 25))
        self.__rental_service.find_and_update_rental(2, 2, datetime.date(2022, 3, 27))
