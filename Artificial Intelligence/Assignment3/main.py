from controller.controller import Controller
from domain.map import Map
from repository.repository import Repository
from utils.generator import RandomGenerator
from view.console import Console


if __name__ == "__main__":
    repository = Repository()
    generator = RandomGenerator()
    controller = Controller(repository, generator)
    console = Console(controller, generator)
    console.run()
