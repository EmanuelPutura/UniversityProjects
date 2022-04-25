from dataclasses import dataclass


@dataclass(eq=False)
class Point:
    """
    Abstract representation of a point in the board
    """
    x: int
    y: int

    def __eq__(self, other):
        """
        Compares two points
        :return: true if the points have the same coordinates, false otherwise
        """
        return self.x == other.x and self.y == other.y
