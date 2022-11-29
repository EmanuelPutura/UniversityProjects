import 'package:football_team_management/domain/football_player.dart';
import 'package:football_team_management/repository/players_repository.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';

class PlayersDatabaseRepository implements PlayersRepository {
  final Database _database;

  static const String tableName = 'Players';

  static const String idColumn = 'id';
  static const String nameColumn = 'name';
  static const String positionColumn = 'position';
  static const String numberColumn = 'number';
  static const String heightColumn = 'height';
  static const String weightColumn = 'weight';

  PlayersDatabaseRepository(this._database);

  static Future<PlayersRepository> init() async {
    var databasesPath = await getDatabasesPath();
    var path = join(databasesPath, 'football_players.db');

    // await deleteDatabase(path);

    // open the database
    var database = await openDatabase(path, version: 1,
        onCreate: (Database db, int version) async {
          // When creating the db, create the table
          await db.execute(
              'CREATE TABLE $tableName ($idColumn INTEGER PRIMARY KEY AUTOINCREMENT, $nameColumn TEXT, '
              '$positionColumn TEXT, $numberColumn INTEGER, $heightColumn INTEGER, $weightColumn REAL)'
          );
        }
    );

    return PlayersDatabaseRepository(database);
  }

  @override
  Future<void> add(FootballPlayer player) async {
    Map<String, dynamic> row = {
      nameColumn : player.name,
      positionColumn : player.position,
      numberColumn: player.number,
      heightColumn: player.height,
      weightColumn: player.weight
    };

    await _database.insert(tableName, row);
  }

  @override
  Future<void> remove(int id) async {
    await _database.delete(tableName, where: "$idColumn = ?", whereArgs: [id]);
  }

  @override
  Future<void> update(int id, FootballPlayer player) async {
    Map<String, dynamic> row = {
      nameColumn : player.name,
      positionColumn : player.position,
      numberColumn: player.number,
      heightColumn: player.height,
      weightColumn: player.weight
    };

    await _database.update(tableName, row, where: "$idColumn = ?", whereArgs: [id]);
  }

  @override
  Future<List<FootballPlayer>> getAll() async {
    var playersAsMaps = await _database.query(tableName);
    List<FootballPlayer> result = [];

    for (var playerMap in playersAsMaps) {
      var player = FootballPlayer(playerMap[nameColumn] as String,
                                  playerMap[positionColumn] as String,
                                  playerMap[numberColumn] as int,
                                  playerMap[heightColumn] as int,
                                  playerMap[weightColumn] as double);

      player.id = playerMap[idColumn] as int;
      result.add(player);
    }

    return result;
  }
}
