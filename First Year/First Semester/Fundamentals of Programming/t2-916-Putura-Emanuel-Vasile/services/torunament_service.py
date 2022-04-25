from random import randint


class TournamentService:
    def __init__(self, player_repository, tournament_repository):
        self.__player_repository = player_repository
        self.__tournament_repository = tournament_repository

    def get_all_players(self):
        return self.__player_repository.data

    def get_players_len(self):
        return len(self.get_all_players())

    def check_if_power2(self, length=None):
        if length is None:
            length = len(self.get_all_players())
        while length != 1:
            if length % 2 == 1:
                return False
            length /= 2
        return True

    def find_upper_2power(self):
        length = len(self.get_all_players())
        while length:
            if self.check_if_power2(length):
                return length
            length -= 1
        return 1

    def get_no_of_eliminated_players(self):
        return self.get_players_len() - self.find_upper_2power()

    def get_fighting_players(self):
        no_of_players = self.get_no_of_eliminated_players() * 2
        all_players = self.get_all_players()
        players = []
        for i in reversed(range(len(all_players))):
            players.append(all_players[i])
            if len(players) == no_of_players:
                break
        return players

    def get_qualified_players(self, winners):
        f_players = self.get_fighting_players()
        for player in self.get_all_players():
            if player.id in winners:
                self.__tournament_repository.add(player)
            elif player in f_players:
                pass
            else:
                self.__tournament_repository.add(player)

    def get_t_qualified_players(self, winners):
        f_players = self.get_fighting_players()
        # print()
        # for player in f_players:
        #     print(player)
        # print()

        for player in self.get_all_players():
            if player.id in winners:
                self.__tournament_repository.add(player)
                # player.strength = player.strength + 1
            elif player in f_players:
                pass

    def get_tournament_qualified_players(self, winners):
        for player in self.get_tournament_players():
            if player.id in winners:
                print(1)
                self.__tournament_repository.add(player)
            else:
                self.__tournament_repository.remove(player)
        for p in self.__tournament_repository.data:
            print(p)

    def establish_pairs(self):
        """
        Established the initial pairs
        :return: the pairs
        """
        players = self.get_fighting_players()
        pairs = []
        while len(players):
            r_index = randint(0, len(players) - 1)
            player1 = players[r_index]
            players.remove(player1)
            r_index = randint(0, len(players) - 1)
            player2 = players[r_index]
            players.remove(player2)
            pairs.append((player1, player2))
        return pairs

    def get_tournament_players(self):
        return self.__tournament_repository.data

    def get_tournament_players_len(self):
        return len(self.get_tournament_players())

    def pair_next_tournament_game(self, players):
        """
        Pairs the next tournament game
        :param players: the players
        :return: the pair
        """
        r_index = randint(0, len(players) - 1)
        player1 = players[r_index]
        players.remove(player1)
        r_index = randint(0, len(players) - 1)
        player2 = players[r_index]
        players.remove(player2)
        return player1, player2

    def play_tournament(self):
        pass

    def get_all_qualified_players(self):
        self.__tournament_repository.data = self.__player_repository.data[:]

    def get_tournament_pairs(self):
        """
        Gets all tournament pairs
        :return: the pairs
        """
        pairs = []
        while len(self.get_tournament_players()):
            pairs.append(self.pair_next_tournament_game(self.get_tournament_players()))
        return pairs

    def update_tournament_players(self, players):
        rem_players = self.get_tournament_players()

