// ignore_for_file: import_of_legacy_library_into_null_safe

import 'dart:async';
import 'dart:collection';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'dart:convert';
import 'package:http/http.dart' as http;

import '../domain/category.dart';
import '../domain/item.dart';
import '../utils/pair.dart';

class DatabaseRepository {
  final WebSocketChannel _channel;

  bool _online = false;
  List<Category> _localCategories = [];
  final Map<String, List<Item>> _categoryToItems = {};

  static const String ipAddress = '10.152.1.86';
  static const String wsPort = '2325';
  static const String httpPort = '2325';

  static const String httpGetCategories = 'categories';
  static const String httpGetItemsWithCategory = 'items';
  static const String httpPostItem = 'item';

  DatabaseRepository(this._channel) {
    _channel.stream.listen((data) {
      _listenToServerHandler(data);
    });
  }

  static Future<DatabaseRepository> init() async {
    final channel = WebSocketChannel.connect(Uri.parse("ws://$ipAddress:$wsPort"));
    return DatabaseRepository(channel);
  }

  Future<void> _listenToServerHandler(String data) async {
  }

  Future<bool> checkOnline() async {
    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetCategories")
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

    return _online;
  }

  Future<Pair> getAllCategories() async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetCategories")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _localCategories = rawRes.map((str) => Category(str)).toList().cast<Category>();

        return Pair(_localCategories, _online);
      } else {
        return Pair(_localCategories, _online);
      }
    } on Exception {
      _online = false;
      return Pair(_localCategories, _online);
    }
  }

  Future<Pair> getItemsWithCategory(String category) async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetItemsWithCategory/$category")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _categoryToItems[category] = rawRes.map((json) => Item.fromJson(json)).toList().cast<Item>();

        return Pair(_categoryToItems[category], _online);
      } else {
        return Pair(_categoryToItems[category], _online);
      }
    } on Exception {
      _online = false;
      return Pair(_categoryToItems[category], _online);
    }
  }

  Future<bool> addItem(Item item) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/$httpPostItem",
          headers: headers,
          body: jsonEncode({
            'name': item.name,
            'description': item.description,
            'image': item.image,
            'category': item.category,
            'units': item.units,
            'price': item.price
          }),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));
    } on Exception {
      _online = false;
    }

    return _online;
  }
}
