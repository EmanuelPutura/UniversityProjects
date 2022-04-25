from src.tests.test_entity import test_entity
from src.tests.test_service import test_service
from src.ui.console import Console

if __name__ == "__main__":
    test_entity()
    test_service()

    console = Console()
    console.run()
