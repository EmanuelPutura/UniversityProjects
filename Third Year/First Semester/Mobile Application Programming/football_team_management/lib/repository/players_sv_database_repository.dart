import 'dart:async';
import 'dart:collection';

import 'package:football_team_management/domain/football_player.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'dart:convert';
import 'dart:developer';
import 'package:http/http.dart' as http;

import '../utils/pair.dart';

class PlayersSvDatabaseRepository {
  final Database _database;
  WebSocketChannel _channel;
  List<FootballPlayer> players;
  bool _online;
  late List<FootballPlayer> _local_db_players;

  static const String tableName = 'Players';

  static const String idColumn = 'id';
  static const String nameColumn = 'name';
  static const String positionColumn = 'position';
  static const String numberColumn = 'number';
  static const String heightColumn = 'height';
  static const String weightColumn = 'weight';

  static const String ipAddress = '172.30.115.177';

  PlayersSvDatabaseRepository(this._database, this._channel, this.players, this._online) {
    _local_db_players = [];
    _channel.stream.listen((data) {
      _listenToServerHandler(data);
    });
  }

  Future<void> _listenToServerHandler(String data) async {
    var listData = data.split('\$');

    if (listData[0] == "ADD") {
      var playerJson = jsonDecode(listData[1]);
      var player = FootballPlayer(playerJson['name'], playerJson['position'],
          playerJson['number'], playerJson['height'], playerJson['weight']);
      player.id = playerJson['id'];
      await _database.insert(tableName, player.toMapWithId());
    } else if (listData[0] == "UPDATE") {
      var player = jsonDecode(listData[1]);
      updateLocally(player['id'], player['name'], player['position'],
          player['number'], player['height'], player['weight']);
    } else if (listData[0] == "DELETE") {
      await removeLocally(int.parse(listData[1]));
    }
  }

  Future<void> checkOnline() async {
    try {
      var response = await http
          .get("http://$ipAddress:5000/")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        if (_online == false) {
          _online = true;
          await _synchronizeServerAndClients();
        }
      }
    } on TimeoutException {
      _online = false;
    } on Error {
      _online = false;
    }
  }

  static Future<PlayersSvDatabaseRepository> init() async {
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

    final channel = WebSocketChannel.connect(Uri.parse("ws://$ipAddress:8765"));
    return PlayersSvDatabaseRepository(database, channel, [], false);
  }

  Future<void> addLocally(String name, String position, int number, int height, double weight) async {
    await _database.insert(
        tableName, FootballPlayer(name, position, number, height, weight).toMap());
  }

  Future<void> removeLocally(int id) async {
    await _database.delete(
      tableName,
      where: ' id = ?',
      whereArgs: [id],
    );
  }

  Future<void> updateLocally(int id, String newName, String newPosition,
      int newNumber, int newHeight, double newWeight) async {
    await _database.update(
      tableName,
      FootballPlayer(newName, newPosition, newNumber, newHeight, newWeight).toMap(),
      where: ' id = ?',
      whereArgs: [id],
    );
  }

  Future<void> _synchronizeServerAndClients() async {
    _channel = WebSocketChannel.connect(Uri.parse("ws://$ipAddress:8765"));
    _channel.stream.listen((data) {
      _listenToServerHandler(data);
    });

    await getLocally();

    var jsonArr = jsonEncode(players);
    Map<String, String> headers = HashMap();
    headers['Accept'] = 'application/json';
    headers['Content-type'] = 'application/json';

    var response = await http.post("http://$ipAddress:5000/player/sync",
        headers: headers,
        body: jsonEncode({
          'players': jsonArr,
        }),
        encoding: Encoding.getByName('utf-8'));

    if (response.statusCode == 200) {
      var res = json.decode(response.body);

      var playersJson = res['players'] as List;
      players =
          playersJson.map((playerJson) => FootballPlayer.fromJson(playerJson)).toList();

      await _database.execute("DELETE FROM $tableName");

      for (var player in players) {
        await _database.insert(tableName, player.toMapWithId());
      }
    }
  }

  Future<Pair> getLocally() async {
    final List<Map<String, dynamic>> maps = await _database.query(tableName);

    players.clear();

    for (var playerMap in maps) {
      var player = FootballPlayer(playerMap['name'] as String, playerMap['position'] as String,
          playerMap['number'] as int, playerMap['height'] as int, playerMap['weight'] as double);

      player.id = playerMap['id'] as int;
      players.add(player);
    }

    return Pair(players, false);
  }

  Future<void> add(FootballPlayer player) async {
    await checkOnline();

    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:5000/player",
          headers: headers,
          body: jsonEncode({
            'name': player.name,
            'position': player.position,
            'number': player.number,
            'height': player.weight,
            'weight': player.weight
          }),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));

      log('cdebug: Added player $player.name');
    } on TimeoutException {
      _online = false;
      _local_db_players.add(player);
      return addLocally(player.name, player.position, player.number, player.height, player.weight);
    } on Error {
      _online = false;
      _local_db_players.add(player);
      return addLocally(player.name, player.position, player.number, player.height, player.weight);
    }
  }

  Future<String> remove(int id) async {
    await checkOnline();
    try {
      var response = await http
          .delete("http://$ipAddress:5000/player/$id")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        log('cdebug: Removed player with id $id');
        return "SUCCESS";
      } else {
        return "ERROR";
      }
    } on TimeoutException {
      _online = false;
      return "OFFLINE";
    } on Error {
      _online = false;
      return "OFFLINE";
    }
  }

  Future<String> update(int id, FootballPlayer player) async {
    await checkOnline();
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .put("http://$ipAddress:5000/player",
          headers: headers,
          body: jsonEncode({
            'id': id,
            'name': player.name,
            'position': player.position,
            'number': player.number,
            'height': player.height,
            'weight': player.weight
          }),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        log('cdebug: Updated player $player.name');
        return "SUCCESS";
      } else {
        return "ERROR";
      }
    } on TimeoutException {
      _online = false;
      return "OFFLINE";
    } on Error {
      _online = false;
      return "OFFLINE";
    }
  }

  Future<Pair> getAll() async {
    var res = await checkOnline();

    try {
      var response = await http
          .get("http://$ipAddress:5000/player")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        var res = json.decode(response.body);

        var playersJson = res['players'] as List;
        players = playersJson
            .map((playerJson) => FootballPlayer.fromJson(playerJson))
            .toList();

        return Pair(players, _online);
      } else {
        return getLocally();
      }
    } on TimeoutException {
      _online = false;
      return getLocally();
    } on Error {
      _online = false;
      return getLocally();
    }
  }
}
