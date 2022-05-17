from utils.utils import MAP_LENGTH


class CellNumericRepresentation:
    NUMERIC_REPRESENTATION_SUPREMUM = MAP_LENGTH ** 2 - 1

    @staticmethod
    def numericRepresentation(x, y):
        return x * MAP_LENGTH + y

    @staticmethod
    def xFromNumericRepresentation(numericRepresentation):
        return numericRepresentation // MAP_LENGTH

    @staticmethod
    def yFromNumericRepresentation(numericRepresentation):
        return numericRepresentation % MAP_LENGTH
