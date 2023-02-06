// ignore_for_file: import_of_legacy_library_into_null_safe

import 'dart:async';
import 'dart:collection';
import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

import '../domain/category.dart';
import '../domain/item.dart';
import '../utils/pair.dart';
import 'package:http/http.dart' as http;

class DbRepository extends ChangeNotifier {
  final WebSocketChannel _channel;

  bool _online = false;
  List<Category> _localCategories = [];
  final Map<String, List<Item>> _categoryToItems = {};
  List<Item> _allItems = [];

  static const String ipAddress = '10.0.2.2';
  static const String wsPort = '2325';
  static const String httpPort = '2325';

  static const String httpGetCategories = 'categories';
  static const String httpGetItemsWithCategory = 'items';
  static const String httpPostAndDeleteItem = 'item';
  static const String httpGetItems = 'discounted';
  static const String httpPostIncrementPrice = 'price';

  String _infoMessage = '';

  DbRepository(this._channel) {
    _channel.stream.listen((data) {
      _listenToServerHandler(data);
    });
  }

  static Future<DbRepository> init() async {
    final channel = WebSocketChannel.connect(Uri.parse("ws://$ipAddress:$wsPort"));
    return DbRepository(channel);
  }

  void _listenToServerHandler(dynamic data) {
    data = jsonDecode(data);
    _infoMessage = data.toString();
    notifyListeners();
  }

  String getInfoMessage() => _infoMessage;

  void setInfoMessage(String message) {
    _infoMessage = message;
    notifyListeners();
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

    notifyListeners();
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

        return Pair(Pair(_localCategories, "ok"), _online);
      } else {
        return Pair(Pair(_localCategories, response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_localCategories, "ok"), _online);
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

        return Pair(Pair(_categoryToItems[category], "ok"), _online);
      } else {
        return Pair(Pair(_categoryToItems[category], response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_categoryToItems[category], "ok"), _online);
  }

  Future<Pair> getAllItems() async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetItems")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _allItems = rawRes.map((json) => Item.fromJson(json)).toList().cast<Item>();

        return Pair(Pair(_allItems, "ok"), _online);
      } else {
        return Pair(Pair(_allItems, response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_allItems, "ok"), _online);
  }

  Future<Pair> addItem(String name, String description, String image, String category, int units, num price) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/$httpPostAndDeleteItem",
          headers: headers,
          body: jsonEncode({
            'name': name,
            'description': description,
            'image': image,
            'category': category,
            'units': units,
            'price': price
          }),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));

      if (response.statusCode != 200) {
        notifyListeners();
        return Pair(response.body, _online);
      }
    } on Exception {
      _online = false;
    }

    notifyListeners();
    return Pair("ok", _online);
  }

  Future<Pair> incrementPrice(int id, num newPrice) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/$httpPostIncrementPrice",
          headers: headers,
          body: jsonEncode({
            'id': id,
            'price': newPrice,
          }),
          encoding: Encoding.getByName('utf-8'))
          .timeout(const Duration(seconds: 1));

      if (response.statusCode != 200) {
        notifyListeners();
        return Pair(response.body, _online);
      }
    } on Exception {
      _online = false;
    }

    notifyListeners();
    return Pair("ok", _online);
  }

  Future<Pair> deleteItem(int id) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .delete("http://$ipAddress:$httpPort/$httpPostAndDeleteItem/$id")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode != 200) {
        notifyListeners();
        return Pair(response.body, _online);
      }
    } on Exception {
      _online = false;
    }

    notifyListeners();
    return Pair("ok", _online);
  }

  Future<Pair> getDiscountedItems() async {
    var pairRepoRes = await getAllItems();
    var allItems = pairRepoRes.left.left as List<Item>;
    var isOnline = pairRepoRes.right;

    allItems.sort((e1, e2) =>
    (e1.price > e2.price || (e1.price == e2.price && e1.units > e2.units)) ? 1 : 0
    );

    var listRes = allItems.take(10).toList();

    return Pair(listRes, isOnline);
  }

  WebSocketChannel getWSChannel() {
    return _channel;
  }
}
