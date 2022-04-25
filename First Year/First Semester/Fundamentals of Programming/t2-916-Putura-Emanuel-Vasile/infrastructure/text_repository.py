from domain.player import Player
from infrastructure.memo_repository import Repository


class TextRepository(Repository):
    def __init__(self, file_name, data=[]):
        super().__init__(data)
        self.__file_name = file_name
        self.__create_file()
        self.__load_file()

    def __create_file(self):
        try:
            with open(self.__file_name, 'x') as file:
                pass
        except Exception:
            pass

    def __load_file(self):
        with open(self.__file_name, 'r') as txt_file:
            for line in txt_file:
                tokens = line.split(',')
                entity = Player(tokens[0], tokens[1], int(tokens[2]))
                super().add(entity)

    def __save_to_file(self, entity):
        with open(self.__file_name, 'a') as txt_file:
            txt_file.write(str(entity) + ';\n')

    def add(self, entity):
        super().add(entity)
        self.__save_to_file(entity)

    def remove(self, id):
        entity = super().remove(id)
        entity_line = str(entity.id) + ';\n'
        with open(self.__file_name, 'r') as txt_file:
            text = txt_file.read()
            text.replace(entity_line, '')
        with open(self.__file_name, 'w') as txt_file:
            txt_file.write(text)
        return entity
