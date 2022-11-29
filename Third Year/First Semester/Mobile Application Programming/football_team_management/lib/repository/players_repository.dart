import 'package:football_team_management/domain/football_player.dart';

abstract class PlayersRepository {
  Future<void> add(FootballPlayer player);

  Future<void> remove(int id);

  Future<void> update(int id, FootballPlayer player);

  Future<List<FootballPlayer>> getAll();
}
