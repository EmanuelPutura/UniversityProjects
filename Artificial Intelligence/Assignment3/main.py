from controller.controller import Controller
from domain.individual import Individual
from repository.repository import Repository
from utils.generator import RandomGenerator
from view.console import Console


if __name__ == "__main__":
    repository = Repository()
    controller = Controller(repository)
    console = Console(controller)
    console.run()
