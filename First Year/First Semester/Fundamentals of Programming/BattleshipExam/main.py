from game_board.board import Board
from presentation.console import ConsoleUI
from services.game_service import GameService

if __name__ == "__main__":
    board = Board()
    game_service = GameService(board)
    consoleUI = ConsoleUI(game_service)
    consoleUI.run()
