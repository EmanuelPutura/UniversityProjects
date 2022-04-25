from domain.player import Player


class PlayerService:
    def __init__(self, player_repository, player_validator):
        self.__player_repository = player_repository
        self.__player_validator = player_validator

    def add_player(self, id, name, strength):
        player = Player(id, name, strength)
        self.__player_repository.validate(player)
        self.__player_repository.add(player)
        return player

    def remove_player(self, id):
        self.__player_repository.remove(id)

    def get_all_sorted_players(self):
        players = self.get_all_players()
        players.sort(key=lambda player: player.strength, reverse=True)
        return players

    def sort_players(self):
        players = self.get_all_sorted_players()
        self.__player_repository.data = players

    def get_all_players(self):
        return self.__player_repository.data
