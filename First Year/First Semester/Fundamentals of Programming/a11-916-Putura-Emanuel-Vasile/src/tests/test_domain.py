import unittest

from domain.cell import Cell, CellState


class TestCell(unittest.TestCase):
    def setUp(self):
        self.__cell = Cell()

    def test_putX(self):
        self.__cell.move_X()
        self.assertEqual(self.__cell.state, CellState.X_OCCUPIED_CELL)

    def test_putO(self):
        self.__cell.move_O()
        self.assertEqual(self.__cell.state, CellState.O_OCCUPIED_CELL)

    def test_free(self):
        self.__cell.free()
        self.assertEqual(self.__cell.state, CellState.FREE_CELL)

    def test_block(self):
        self.__cell.block()
        self.assertEqual(self.__cell.state, CellState.BLOCKED_CELL)

    def test_str(self):
        self.__cell.move_X()
        self.assertEqual(str(self.__cell), 'X')
