import unittest

from game_board.board import Board
from game_board.cell import CellState
from services.game_service import GameService, ServiceError


class TestShipCommand(unittest.TestCase):
    def test_ship_command(self):
        board = Board()
        game_service = GameService(board)
        game_service.place_ship([[1, 1]])
        self.assertEqual(board[1][1].state, CellState.PLAYER_SHIP)
        game_service.place_ship([[2, 2], [2, 3]], False)
        self.assertEqual(board[2][2].state, CellState.COMPUTER_SHIP)
        self.assertEqual(board[3][2].state, CellState.COMPUTER_SHIP)
        self.assertRaises(ServiceError, game_service.place_ship, [[1, 1]], False)
        game_service.place_ship([[3, 3]])
        game_service.place_ship([[4, 4]])
        self.assertEqual(game_service.human_ships[0], [[4, 4]])

    def test_past_ships(self):
        board = Board()
        game_service = GameService(board)
        game_service.place_ship([[1, 1], [1, 2]])
        game_service.place_ship([[3, 3]])
        game_service.place_ship([[4, 4]])
        self.assertEqual(board[1][1].state, CellState.FREE)
        self.assertEqual(board[1][2].state, CellState.FREE)
        self.assertEqual(board[3][3].state, CellState.PLAYER_SHIP)
        self.assertEqual(board[4][4].state, CellState.PLAYER_SHIP)
