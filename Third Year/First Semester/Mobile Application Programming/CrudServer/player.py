class Player:
    def __init__(self, id: int, name: str, position: str, number: int, height: int, weight: float):
        self.id = id
        self.name = name
        self.position = position
        self.number = number
        self.height = height
        self.weight = weight

    def as_dict(self):
        return {'id': self.id, 'name': self.name, 'position': self.position, 'number': self.number, 'height': self.height, 'weight': self.weight}
