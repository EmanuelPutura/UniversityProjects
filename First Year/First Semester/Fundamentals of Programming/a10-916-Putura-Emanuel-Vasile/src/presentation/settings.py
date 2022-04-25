from erros.exceptions import SettingsError
from infrastructure.binary_repository import MovieBinaryRepository, ClientBinaryRepository, RentalBinaryRepository
from infrastructure.data_access import MovieDataAccess, ClientDataAccess, RentalDataAccess
from infrastructure.database_repository import RentalDatabaseRepository, MovieDatabaseRepository, \
    ClientDatabaseRepository
from infrastructure.json_repository import MovieJSONRepository, ClientJSONRepository, RentalJSONRepository
from infrastructure.memory_repositories import MovieRepository, ClientRepository, RentalRepository
from infrastructure.text_repositories import MovieTextRepository, ClientTextRepository, RentalTextRepository


class Settings:
    def __init__(self):
        self.__repository = self.__movies = self.__clients = self.__rentals = self.__ui = self.__database = ''

    def set_repository(self, other):
        self.__repository = other

    def set_movies(self, other):
        self.__movies = other

    def set_clients(self, other):
        self.__clients = other

    def set_rentals(self, other):
        self.__rentals = other

    def set_ui(self, other):
        self.__ui = other

    def set_database(self, other):
        self.__database = other

    def load_data(self, file_name='data/settings.properties.txt'):
        operations = {'repository': self.set_repository, 'movies': self.set_movies, 'clients': self.set_clients,
                      'rentals': self.set_rentals, 'ui': self.set_ui, 'database': self.set_database}
        with open(file_name, 'r') as file:
            for line in file:
                line = line.replace('"', '')
                tokens = line.split('=')
                operations[tokens[0].strip()](tokens[1].strip())

    def get_options(self):
        return self.__repository + ';' + self.__movies + ';' + self.__clients + ';' + self.__rentals + ';' + self.__ui + ';' + self.__database


class SettingsManager:
    def configure_options(self, options):
        repository_option = {'inmemory': self.__configure_memo_repository, 'textfiles': self.__configure_text_repository,
                             'binaryfiles': self.__configure_binary_repository, 'jsonfiles': self.__configure_json_repository,
                             'database': self.__configure_database_repository}
        tokens = options.split(';')
        repositories = repository_option[tokens[0]](tokens[1], tokens[2], tokens[3], tokens[5])
        ui_option = self.__configure_ui(tokens[4])
        if not ui_option:
            raise SettingsError('Invalid UI settings.\n')
        return ui_option, *repositories

    def __memo_populate(self, movie_service, client_service):
        movie_service.generate_movies()
        client_service.generate_clients()

    def __configure_memo_repository(self, movies_file, clients_file, rentals_file, database_path):
        return MovieRepository(), ClientRepository(), RentalRepository()

    def __configure_text_repository(self, movies_file, clients_file, rentals_file, database_path):
        return MovieTextRepository(MovieDataAccess(), movies_file), ClientTextRepository(ClientDataAccess(), clients_file), \
               RentalTextRepository(RentalDataAccess(), rentals_file)

    def __configure_binary_repository(self, movies_file, clients_file, rentals_file, database_path):
        return MovieBinaryRepository(movies_file), ClientBinaryRepository(clients_file), RentalBinaryRepository(rentals_file)

    def __configure_json_repository(self, movies_file, clients_file, rentals_file, database_path):
        return MovieJSONRepository(movies_file), ClientJSONRepository(clients_file), RentalJSONRepository(rentals_file)

    def __configure_database_repository(self, movies_file, clients_file, rentals_file, database_path):
        return MovieDatabaseRepository(MovieDataAccess(), database_path), ClientDatabaseRepository(ClientDataAccess(), database_path), \
               RentalDatabaseRepository(RentalDataAccess(), database_path)

    def __configure_ui(self, ui_option):
        if ui_option.lower() == 'console':
            return 1
        elif ui_option.lower() == 'gui':
            return 2
        return 0

    def configure_populate(self, options, movie_service, client_service):
        if options.split(';')[0] == 'inmemory':
            self.__memo_populate(movie_service, client_service)
