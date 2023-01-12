import 'dart:collection';

import 'package:animal_shelter/pair.dart';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';
import 'package:http/http.dart' as http;
import 'package:web_socket_channel/web_socket_channel.dart';
import 'dart:convert';
import 'dart:async';

import 'animal.dart';

class AnimalRepository {
  final Database _database;
  WebSocketChannel _channel;
  List<Animal> animals;
  bool _isOnline;
  late List<Animal> _local_animals;

  AnimalRepository(
      this._database, this._channel, this.animals, this._isOnline) {
    _local_animals = [];
    _channel.stream.listen((data) {
      _listenHandle(data);
    });
  }

  Future<void> _synchronize() async {
    _channel = WebSocketChannel.connect(Uri.parse("ws://172.20.10.7:8765"));
    await getAnimalsLocal();
    var jsonArr = jsonEncode(animals);
    Map<String, String> headers = HashMap();
    headers['Accept'] = 'application/json';
    headers['Content-type'] = 'application/json';

    var response = await http.post("http://172.20.10.7:5000/animal/sync",
        headers: headers,
        body: jsonEncode({
          'animals': jsonArr,
        }),
        encoding: Encoding.getByName('utf-8'));

    if (response.statusCode == 200) {
      var res = json.decode(response.body);

      var animalsJson = res['animals'] as List;
      animals =
          animalsJson.map((animalJson) => Animal.fromJson(animalJson)).toList();

      await _database.execute("DELETE FROM animals");

      for (var animal in animals) {
        await _database.insert('animals', animal.toMapWithId());
      }
    }
  }

  Future<void> _listenHandle(String data) async {
    var listData = data.split('\$');

    if (listData[0] == "ADD") {
      var animalJson = jsonDecode(listData[1]);
      var animal = Animal(animalJson['name'], animalJson['age'],
          animalJson['breed'], animalJson['description']);
      animal.id = animalJson['id'];
      await _database.insert('animals', animal.toMapWithId());
    } else if (listData[0] == "UPDATE") {
      var animal = jsonDecode(listData[1]);
      updateAnimalLocal(animal['id'], animal['name'], animal['age'],
          animal['breed'], animal['description']);
    } else if (listData[0] == "DELETE") {
      await removeAnimalLocal(int.parse(listData[1]));
    }
  }

  static Future<AnimalRepository> init() async {
    var databasePath = await getDatabasesPath();
    var path = join(databasePath, 'animals_database.db');

    var database =
        await openDatabase(path, version: 1, onCreate: (db, version) async {
      await db.execute(
        'CREATE TABLE animals(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER,'
        'breed TEXT, description TEXT)',
      );
    });

    final channel =
        WebSocketChannel.connect(Uri.parse("ws://172.20.10.7:8765"));

    return AnimalRepository(database, channel, [], false);
  }

  Future<void> addAnimalLocal(
      String name, int age, String breed, String description) async {
    await _database.insert(
        'animals', Animal(name, age, breed, description).toMap());
  }

  Future<void> addAnimal(
      String name, int age, String breed, String description) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://172.20.10.7:5000/animal",
              headers: headers,
              body: jsonEncode({
                'name': name,
                'age': age,
                'breed': breed,
                'description': description
              }),
              encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 3));

      if (response.statusCode == 200) {
        if (_isOnline == false) {
          _isOnline = true;
          await _synchronize();
        }
      }
    } on TimeoutException {
      _isOnline = false;
      _local_animals.add(Animal(name, age, breed, description));
      return addAnimalLocal(name, age, breed, description);
    } on Error {
      _isOnline = false;
      _local_animals.add(Animal(name, age, breed, description));
      return addAnimalLocal(name, age, breed, description);
    }
  }

  Future<void> removeAnimalLocal(int id) async {
    await _database.delete(
      'animals',
      where: ' id = ?',
      whereArgs: [id],
    );
  }

  Future<String> removeAnimal(int id) async {
    try {
      var response = await http
          .delete("http://172.20.10.7:5000/animal/$id")
          .timeout(const Duration(seconds: 3));

      if (_isOnline == false) {
        _isOnline = true;
        await _synchronize();
      }

      if (response.statusCode == 200) {
        return "SUCCESS";
      } else {
        return "ERROR";
      }
    } on TimeoutException {
      _isOnline = false;
      return "OFFLINE";
    } on Error {
      _isOnline = false;
      return "OFFLINE";
    }
  }

  Future<void> updateAnimalLocal(int id, String newName, int newAge,
      String newBreed, String newDescription) async {
    await _database.update(
      'animals',
      Animal(newName, newAge, newBreed, newDescription).toMap(),
      where: ' id = ?',
      whereArgs: [id],
    );
  }

  Future<String> updateAnimal(
      int id, String name, int age, String breed, String description) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .put("http://172.20.10.7:5000/animal",
              headers: headers,
              body: jsonEncode({
                'id': id,
                'name': name,
                'age': age,
                'breed': breed,
                'description': description
              }),
              encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 3));

      if (_isOnline == false) {
        _isOnline = true;
        await _synchronize();
      }

      if (response.statusCode == 200) {
        return "SUCCESS";
      } else {
        return "ERROR";
      }
    } on TimeoutException {
      _isOnline = false;
      return "OFFLINE";
    } on Error {
      _isOnline = false;
      return "OFFLINE";
    }
  }

  Future<Pair> getAnimalsLocal() async {
    final List<Map<String, dynamic>> maps = await _database.query('animals');

    animals.clear();

    for (var animalMap in maps) {
      var animal = Animal(animalMap['name'] as String, animalMap['age'] as int,
          animalMap['breed'] as String, animalMap['description'] as String);

      animal.id = animalMap['id'] as int;
      animals.add(animal);
    }

    return Pair(animals, false);
  }

  Future<Pair> getAnimals() async {
    try {
      var response = await http
          .get("http://172.20.10.7:5000/animal")
          .timeout(const Duration(seconds: 3));

      if (response.statusCode == 200) {
        if (_isOnline == false) {
          _isOnline = true;
          await _synchronize();
        }
        var res = json.decode(response.body);

        var animalsJson = res['animals'] as List;
        animals = animalsJson
            .map((animalJson) => Animal.fromJson(animalJson))
            .toList();

        return Pair(animals, _isOnline);
      } else {
        return getAnimalsLocal();
      }
    } on TimeoutException {
      _isOnline = false;
      return getAnimalsLocal();
    } on Error {
      _isOnline = false;
      return getAnimalsLocal();
    }
  }
}
