from controller.controller import Controller
from domain.map import Map
from repository.repository import Repository
from view.console import Console


if __name__ == "__main__":
    repository = Repository()
    controller = Controller(repository)
    console = Console(controller)
    console.run()
