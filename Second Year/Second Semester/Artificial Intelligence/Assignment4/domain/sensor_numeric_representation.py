from utils.utils import MAP_LENGTH, MAX_ENERGY_LEVEL


# energy level should always be less than MAX_LENGTH
class SensorNumericRepresentation:
    NUMERIC_REPRESENTATION_SUPREMUM = MAP_LENGTH ** 3 - 2 * MAP_LENGTH + MAP_LENGTH ** 2 + MAX_ENERGY_LEVEL - 1

    @staticmethod
    def numericRepresentation(sensor):
        return sensor.x * MAP_LENGTH * MAP_LENGTH + sensor.y * MAP_LENGTH + sensor.energy

    @staticmethod
    def xFromNumericRepresentation(numericRepresentation):
        return numericRepresentation // (MAP_LENGTH ** 2)

    @staticmethod
    def yFromNumericRepresentation(numericRepresentation):
        return (numericRepresentation % (MAP_LENGTH ** 2)) // MAP_LENGTH

    @staticmethod
    def energyFromNumericRepresentation(numericRepresentation):
        return (numericRepresentation % (MAP_LENGTH ** 2)) % MAP_LENGTH
