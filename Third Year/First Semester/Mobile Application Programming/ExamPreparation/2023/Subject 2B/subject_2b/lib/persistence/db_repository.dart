// ignore_for_file: import_of_legacy_library_into_null_safe

import 'dart:async';
import 'dart:collection';
import 'dart:convert';
import 'dart:developer';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:path/path.dart';
import 'package:subject_2b/utils/http_out_message.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:sqflite/sqflite.dart';
import 'package:http/http.dart' as http;

import '../domain/activity.dart';

class DbRepository extends ChangeNotifier {
  final WebSocketChannel _channel;

  final Database _categoriesDatabase;
  final Database _activitiesDatabase;

  static const String categoriesTableName = 'Categories';
  static const String categoriesNameColumn = 'name';

  static const String activitiesTableName = 'Activities';
  static const String activitiesIdColumn = 'id';
  static const String activitiesNameColumn = 'name';
  static const String activitiesDescriptionColumn = 'description';
  static const String activitiesCategoryColumn = 'category';
  static const String activitiesDateColumn = 'date';
  static const String activitiesTimeColumn = 'time';
  static const String activitiesIntensityColumn = 'intensity';

  bool _online = false;
  bool firstCall = false;
  String _infoMessage = '';

  List<String> _localCategories = [];
  List<Activity> _localActivities = [];
  final Map<String, List<Activity>> _categoryToActivities = {};

  static const String ipAddress = '10.0.2.2';
  static const String wsPort = '2302';
  static const String httpPort = '2302';

  static Future<Database> _createDatabase(String dbName, String createQuery) async {
    var databasesPath = await getDatabasesPath();
    var path = join(databasesPath, dbName);

    // await deleteDatabase(path);

    // open the database
    return await openDatabase(path, version: 1,
        onCreate: (Database db, int version) async {
          // When creating the db, create the table
          await db.execute(createQuery);
        }
    );
  }

  static Future<DbRepository> init() async {
    final channel = WebSocketChannel.connect(Uri.parse("ws://$ipAddress:$wsPort"));

    // TODO: no need for two separate DBs
    final categoriesDb = await DbRepository._createDatabase(
      'categories.db',
      'CREATE TABLE $categoriesTableName ($categoriesNameColumn TEXT)'
    );

    final activitiesDb = await DbRepository._createDatabase(
      'activities.db',
      'CREATE TABLE $activitiesTableName ($activitiesIdColumn INTEGER PRIMARY KEY,'
      '$activitiesNameColumn TEXT, '
      '$activitiesDescriptionColumn TEXT, '
      '$activitiesCategoryColumn TEXT, '
      '$activitiesDateColumn TEXT, '
      '$activitiesTimeColumn INT,'
      '$activitiesIntensityColumn TEXT)'
    );

    return DbRepository(channel, categoriesDb, activitiesDb);
  }

  DbRepository(this._channel, this._categoriesDatabase, this._activitiesDatabase) {
    _channel.stream.listen((data) {
      _listenToServerHandler(data);
    });
  }

  void _listenToServerHandler(dynamic data) {
    data = jsonDecode(data);
    _infoMessage = data.toString();
    notifyListeners();
  }

  WebSocketChannel getWSChannel() {
    return _channel;
  }

  String getInfoMessage() => _infoMessage;

  void setInfoMessage(String message) {
    _infoMessage = message;
    notifyListeners();
  }

  /*
    Attempt to make a dummy request and see if it succeeds
   */
  Future<bool> checkOnline() async {
    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/categories")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        if (_online == false) {
          _online = true;
        }
      }
    } on TimeoutException {
      _online = false;
    } on Error {
      _online = false;
    }

    notifyListeners();
    return _online;
  }

  Future<HttpOutMessage<List<String>>> getAllCategories() async {
    _online = false;

    if (!firstCall) {
      await _loadAllCategoriesFromLocalDb();
      await _loadAllActivitiesFromLocalDb();
      firstCall = true;
    }

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/categories")
          .timeout(const Duration(seconds: 1));

      var serverStatus = response.body;
      if (response.statusCode == 200) {
        _online = true;

        _localCategories = json.decode(response.body).toList().cast<String>();
        for (var i = 0; i < _localCategories.length; ++i) {
          _addToLocalCategoriesDb(_localCategories[i]);
        }

        serverStatus = HttpOutMessage.okServerMessage;
      }

      return HttpOutMessage(_localCategories, serverStatus, _online);
    } on Exception catch(e) {
      log("Error at getting all!");
      _online = false;
      return HttpOutMessage(_localCategories, e.toString(), _online);
    }
  }

  Future<HttpOutMessage<List<Activity>>> getAllActivitiesWithCategory(String category) async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/activities/$category")
          .timeout(const Duration(seconds: 1));

      var serverStatus = response.body;
      if (response.statusCode == 200) {
        _online = true;

        var jsonRes = json.decode(response.body);

        _categoryToActivities[category] = jsonRes.map((json) => Activity.fromJson(json)).toList().cast<Activity>();
        final newActivities = _categoryToActivities[category] ?? [];

        for (var i = 0; i < newActivities.length; ++i) {
          _addToLocalActivitiesDb(newActivities[i]);
        }

        serverStatus = HttpOutMessage.okServerMessage;
      }

      return HttpOutMessage(_categoryToActivities[category] ?? [], serverStatus, _online);
    } on Exception catch(e) {
      _online = false;
      log("Error at getting all with!");
      return HttpOutMessage(_categoryToActivities[category] ?? [], e.toString(), _online);
    }
  }

  Future<HttpOutMessage<List<String>>> addActivity(String name, String description, String category, DateTime date, int time, String intensity) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/activity",
          headers: headers,
          body: jsonEncode(
            Activity(name, description, category, date, time, intensity).toJsonWithoutId()
          ),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));

      if (response.statusCode != 200) {
        notifyListeners();
        return HttpOutMessage([], response.body, _online);
      }
    } on Exception catch(e) {
      _online = false;
      log("Error at add!");

      notifyListeners();
      return HttpOutMessage([], e.toString(), _online);
    }

    notifyListeners();
    return HttpOutMessage([], HttpOutMessage.okServerMessage, _online);
  }

  Future<HttpOutMessage<List<String>>> deleteActivity(int id) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .delete("http://$ipAddress:$httpPort/activity/$id")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode != 200) {
        notifyListeners();
        return HttpOutMessage([], response.body, _online);
      }
    } on Exception catch(e) {
      _online = false;

      log("Error at delete!");
      notifyListeners();
      return HttpOutMessage([], e.toString(), _online);
    }

    notifyListeners();
    return HttpOutMessage([], HttpOutMessage.okServerMessage, _online);
  }

  Future<HttpOutMessage<List<String>>> updateIntensity(int id, String intensity) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/intensity",
          headers: headers,
          body: jsonEncode({
            'id': id,
            'intensity': intensity
          }),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));

      if (response.statusCode != 200) {
        notifyListeners();
        return HttpOutMessage([], response.body, _online);
      }
    } on Exception catch(e) {
      _online = false;

      log("Error at getting update!");
      notifyListeners();
      return HttpOutMessage([], e.toString(), _online);
    }

    notifyListeners();
    return HttpOutMessage([], HttpOutMessage.okServerMessage, _online);
  }

  Future<HttpOutMessage<List<Activity>>> getAllActivities() async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/easiest")
          .timeout(const Duration(seconds: 1));

      var serverStatus = response.body;
      if (response.statusCode == 200) {
        _online = true;

        var jsonRes = json.decode(response.body);

        _localActivities = jsonRes.map((json) => Activity.fromJson(json)).toList().cast<Activity>();
        for (var i = 0; i < _localActivities.length; ++i) {
          _addToLocalActivitiesDb(_localActivities[i]);
        }

        _populateCategoryToActivityMap(_localActivities);
        _populateCategoriesFromActivities(_localActivities);

        serverStatus = HttpOutMessage.okServerMessage;
      }

      return HttpOutMessage(_localActivities, serverStatus, _online);
    } on Exception catch(e) {
      log("Error at getting all!");
      _online = false;
      return HttpOutMessage(_localActivities, e.toString(), _online);
    }
  }

  Future<HttpOutMessage<List<Activity>>> getEasiestActivities() async {
    var httpOutMessage = await getAllActivities();
    var allActivities = httpOutMessage.collection;

    allActivities.sort((a1, a2) => (
      a1.compareTo(a2)
    ));

    var listRes = allActivities.take(10).toList();
    return HttpOutMessage(listRes, httpOutMessage.serverResponse, httpOutMessage.online);
  }

  void _populateCategoryToActivityMap(List<Activity> activities) {
    for (var i = 0; i < activities.length; i++) {
      _categoryToActivities.update(
        activities[i].category,
        (value) => value.followedBy({activities[i]}).toList(),
        ifAbsent: () => {activities[i]}.toList() ,
      );
    }
  }

  void _populateCategoriesFromActivities(List<Activity> activities) {
    for (var i = 0; i < activities.length; i++) {
      if (!_localCategories.contains(activities[i].category)) {
        _localCategories.add(activities[i].category);
        _addToLocalCategoriesDb(activities[i].category);
      }
    }
  }

  Future<void> _addToLocalCategoriesDb(String category) async {
    Map<String, dynamic> row = {
      categoriesNameColumn : category
    };

    await _categoriesDatabase.insert(categoriesTableName, row);
  }

  Future<void> _loadAllCategoriesFromLocalDb() async {
    var categoriesAsMaps = await _categoriesDatabase.query(categoriesTableName);

    for (var categoryMap in categoriesAsMaps) {
      var category = categoryMap[categoriesNameColumn] as String;

      if (!_localCategories.contains(category)) {
        _localCategories.add(category);
      }
    }
  }

  Future<void> _addToLocalActivitiesDb(Activity activity) async {
    Map<String, dynamic> row = {
      activitiesIdColumn: activity.id,
      activitiesNameColumn: activity.name,
      activitiesDescriptionColumn: activity.description,
      activitiesCategoryColumn: activity.category,
      activitiesDateColumn: activity.date.toIso8601String(),
      activitiesTimeColumn: activity.time,
      activitiesIntensityColumn: activity.intensity,
    };

    try {
      await _activitiesDatabase.insert(activitiesTableName, row);
    } on Exception {
      log("Add to local activities exception!");
    }
  }

  Future<void> _loadAllActivitiesFromLocalDb() async {
    _localActivities.clear();
    var activitiesAsMaps = await _activitiesDatabase.query(activitiesTableName);

    for (var activityMap in activitiesAsMaps) {
      var activity = Activity(
        activityMap[activitiesNameColumn] as String,
        activityMap[activitiesDescriptionColumn] as String,
        activityMap[activitiesCategoryColumn] as String,
        DateTime.parse(activityMap[activitiesDateColumn] as String),
        activityMap[activitiesTimeColumn] as int,
        activityMap[activitiesIntensityColumn] as String
      );

      if (!_localActivities.contains(activity)) {
        _localActivities.add(activity);
      }
    }

    _populateCategoryToActivityMap(_localActivities);
  }
}
