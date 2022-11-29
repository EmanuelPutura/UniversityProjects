import 'package:football_team_management/domain/football_player.dart';
import 'package:football_team_management/repository/players_repository.dart';

class PlayersMemoryRepository implements PlayersRepository {
  final List<FootballPlayer> elements = [];

  @override
  Future<void> add(FootballPlayer player) async {
    elements.add(player);
  }

  @override
  Future<void> remove(int id) async {
    FootballPlayer player = elements.where((element) => element.id == id).first;
    elements.remove(player);
  }

  @override
  Future<void> update(int id, FootballPlayer player) async {
    player.id = id;
    elements[elements.indexWhere((element) => element.id == id)] = player;
  }

  @override
  Future<List<FootballPlayer>> getAll() async {
    return elements;
  }
}
