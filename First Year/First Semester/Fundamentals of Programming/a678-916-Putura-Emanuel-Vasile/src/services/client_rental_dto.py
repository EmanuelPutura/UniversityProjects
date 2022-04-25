from colors.color import Color


class ClientRentalDTO:
    def __init__(self, client, rental_days_number):
        self.__client = client
        self.__rental_days_number = rental_days_number

    @property
    def client(self):
        return self.__client

    @property
    def rental_days_number(self):
        return self.__rental_days_number

    def __str__(self):
        str_representation = ' ClientID: {} '.format(self.client.id).ljust(30, '-').rjust(45, '-') + '\n'
        str_representation += "--Name: '{}'\n".format(self.client.name)
        str_representation += "--Number of movie rental days: {}\n".format(self.__rental_days_number)
        str_representation += ''.rjust(45, '-') + '\n'
        return Color.OKGREEN + str_representation + Color.ENDC

    def gui_str(self):
        str_representation = '-' * 5 + ' Client ID: {}'.format(self.client.id) + '\n'
        str_representation += '-' * 5 + ' Name: {}'.format(self.client.name) + '\n'
        str_representation += '-' * 5 + 'Number of movie rental days: {}'.format(self.__rental_days_number) + '\n'
        str_representation += '-' * 100 + '\n'
        return str_representation

    def __eq__(self, other):
        return self.__client == other.client and self.__rental_days_number == other.rental_days_number


class ClientRentalAssembler:
    @staticmethod
    def create_dto(client, days_rental_number):
        return ClientRentalDTO(client, days_rental_number)
