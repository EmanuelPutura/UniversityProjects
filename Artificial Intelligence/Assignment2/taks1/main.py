from taks1.controller.controller import Controller
from taks1.view.gui import Gui

if __name__ == "__main__":
    controller = Controller()
    gui = Gui(controller)
    gui.run()
