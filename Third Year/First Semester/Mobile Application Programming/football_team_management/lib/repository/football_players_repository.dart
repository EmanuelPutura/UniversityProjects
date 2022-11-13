import 'package:football_team_management/domain/football_player.dart';

class FootballPlayersRepository {
  final List<FootballPlayer> elements = [];

  void add(FootballPlayer player) {
    elements.add(player);
  }

  void remove(int id) {
    FootballPlayer player = elements.where((element) => element.id == id).first;
    elements.remove(player);
  }

  void update(int id, FootballPlayer player) {
    player.id = id;
    elements[elements.indexWhere((element) => element.id == id)] = player;
  }
}
