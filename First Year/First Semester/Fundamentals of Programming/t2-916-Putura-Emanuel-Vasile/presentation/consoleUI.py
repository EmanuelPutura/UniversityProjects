class ConsoleUI:
    def __init__(self, player_service, tournament_service):
        self.__player_service = player_service
        self.__tournament_service = tournament_service
        self.__commands = {'display': self.__display_players, 'playq': self.__play_qualifying_round, 'playt': self.__play_tournament}

    def __display_players(self):
        players = self.__player_service.get_all_sorted_players()
        for player in players:
            print(player)
        print()

    def __play_qualifying_round(self):
        players = self.__player_service.get_all_sorted_players()
        if self.__tournament_service.check_if_power2():
            self.__tournament_service.get_all_qualified_players()
            print('Qualifying round not playable')
            return
        pairs = self.__tournament_service.establish_pairs()
        winners = []
        for pair in pairs:
            print('Choose your winner by typing its ID, options are: ')
            print(pair[0])
            print(pair[1])
            ids = [pair[0].id, pair[1].id]
            winner_id = None
            while winner_id not in ids:
                if winner_id is not None:
                    print('Invalid ID.')
                winner_id = input('winner ID > ')
            winners.append(winner_id)
        self.__tournament_service.get_qualified_players(winners)

    def __play_tournament(self):
        players = self.__tournament_service.get_tournament_players()
        if not len(players):
            print('Qualification round has not been played yet.')
            print('We play it now.')
        self.__play_qualifying_round()
        players = self.__tournament_service.get_tournament_players()
        while len(players) != 1:
            print('Last {} round:'.format(len(players)))
            pairs = self.__tournament_service.get_tournament_pairs()
            winners = []
            for pair in pairs:
                print('Choose your winner by typing its ID, options are: ')
                print(pair[0])
                print(pair[1])
                winner_id = input('winner ID > ')
                winners.append(winner_id)
            self.__tournament_service.get_qualified_players(winners)
            players = self.__tournament_service.get_tournament_players()
        winning_player = players[0]
        print("Player '{}' has won the game.".format(str(winning_player)))

    def __print_menu(self):
        print('\n' + '-' * 15 + ' Generic Application ' + '-' * 15)
        print(' display - Display all players from the input file, sorted descending by playing strength')
        print(' playq - Play the qualifying round')
        print(' playt - Play the tournament')
        print(' exit - exit the application')
        print('-' * 51 + '\n')

    def run(self):
        running = True
        while running:
            try:
                self.__print_menu()
                command = input('command > ').strip()
                if command == 'exit':
                    break
                elif command in self.__commands:
                    self.__commands[command]()
                else:
                    print("'{}' is not a valid command.".format(command))
            except Exception as exception:
                print('Unexpected exception occurred: ' + str(exception))
