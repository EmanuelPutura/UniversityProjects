"""
Assemble the program and start the user interface here
"""

from src.ui.console import start_command_ui
from src.functions.functions import test_functions

test_functions()
start_command_ui()
