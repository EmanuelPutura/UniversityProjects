"""
3. Movie Rental
Write an application for movie rentals. The application will store:

Movie: movie_id, title, description, genre
Client: client_id, name
Rental: rental_id, movie_id, client_id, rented_date, due_date, returned_date

Create an application which allows to:

    1. Manage clients and books. The user can add, remove, update, and list both clients and books.
    2. Rent or return a book. A client can rent an available book.
    A client can return a rented book at any time. Only available books can be rented.
"""
from infrastructure.repositories import MovieRepository, ClientRepository, RentalRepository
from presentation.GUI import GUI
from presentation.console import Console, ChooseConsole
from services.client_service import ClientService
from services.movie_service import MovieService
from services.rental_service import RentalService
from validation.client_validator import ClientValidator
from validation.movie_validator import MovieValidator
from validation.rental_validator import RentalValidator

if __name__ == "__main__":
    movie_validator = MovieValidator()
    client_validator = ClientValidator()
    rental_validator = RentalValidator()
    movie_repository = MovieRepository()
    client_repository = ClientRepository()
    rental_repository = RentalRepository()
    movie_service = MovieService(movie_validator, movie_repository)
    movie_service.generate_movies()
    client_service = ClientService(client_validator, client_repository)
    client_service.generate_clients()
    rental_service = RentalService(rental_validator, rental_repository, movie_repository, client_repository)

    chooseConsole = ChooseConsole()
    option = chooseConsole.run()

    if option == 1:
        console = Console(movie_service, client_service, rental_service)
        console.run()
    elif option == 2:
        gui = GUI(movie_service, client_service, rental_service)
        gui.run()
