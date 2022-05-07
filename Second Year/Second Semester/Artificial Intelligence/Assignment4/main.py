from controller.sensors_order_and_energy_controller import SensorsOrderAndEnergyController
from controller.sensors_order_controller import SensorsOrderController
from domain.map import Map
from repository.repository import Repository
from view.console import Console


if __name__ == "__main__":
    map = Map()
    repository = Repository(map)
    # controller = SensorsOrderController(repository)
    controller = SensorsOrderAndEnergyController(repository)
    console = Console(controller)
    console.run()
