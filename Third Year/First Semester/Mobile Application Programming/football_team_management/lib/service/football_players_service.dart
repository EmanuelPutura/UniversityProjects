import 'package:flutter/material.dart';
import 'package:football_team_management/repository/players_repository.dart';
import '../domain/football_player.dart';
import '../repository/players_database_repository.dart';

class FootballPlayersService extends ChangeNotifier {
  final PlayersRepository _repository;

  FootballPlayersService(this._repository);

  static Future<FootballPlayersService> init() async {
    var repository = await PlayersDatabaseRepository.init();
    return FootballPlayersService(repository);
  }

  void loadDefaultPlayers() {
    List<FootballPlayer> defaultPLayers = [
      FootballPlayer('Tavi Popescu', 'LW', 10, 178, 75.5),
      FootballPlayer('Andrei Cordea', 'RW', 98, 175, 77),
      FootballPlayer('Ianis Stoica', 'ST', 10, 176, 78.5),
      FootballPlayer('Andrea Compagno', 'ST', 10, 195, 81.5),
      FootballPlayer('Florinel Coman', 'LW', 10, 177, 80.5),
      FootballPlayer('Andrei Sut', 'CDM', 10, 178, 75.7),
      FootballPlayer('Andrei Vlad', 'GK', 10, 186, 74.5),
      FootballPlayer('Iulian Cristea', 'CB', 2, 182, 79.5),
      FootballPlayer('Valentin Cretu', 'RB', 13, 177, 80.5),
      FootballPlayer('Andrei Pantea', 'LB', 4, 178, 75.7),
      FootballPlayer('Risto Radunovic', 'LB', 5, 186, 74.5),
      FootballPlayer('Darius Olaru', 'CM', 8, 182, 79.5),
      FootballPlayer('Joonas Tamm', 'CB', 22, 186, 74.5),
      FootballPlayer('Billel Omrani', 'ST', 99, 182, 79.5),
    ];

    for (var i = 0; i < defaultPLayers.length; ++i) {
      _repository.add(defaultPLayers[i]);
    }

    notifyListeners();
  }

  void add(String name, String position, int number, int height, double weight) {
    _repository.add(FootballPlayer(name, position, number, height, weight));
    notifyListeners();
  }

  void remove(int id) {
    _repository.remove(id);
    notifyListeners();
  }

  void update(int id, String name, String position, int number, int height, double weight) {
    _repository.update(id, FootballPlayer(name, position, number, height, weight));
    notifyListeners();
  }

  Future<List<FootballPlayer>> getAllPlayers() async => await _repository.getAll();
}
