// ignore_for_file: import_of_legacy_library_into_null_safe

import 'dart:async';
import 'dart:collection';
import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

import 'package:http/http.dart' as http;

import '../domain/document.dart';
import '../utils/pair.dart';

class DbRepository extends ChangeNotifier {
  final WebSocketChannel _channel;

  bool _online = false;

  List<Document> _localDocuments = [];

  static const String ipAddress = '192.168.43.241';
  static const String wsPort = '2701';
  static const String httpPort = '2701';

  static const String usernameKey = 'username';

  String _infoMessage = '';
  String _username;

  DbRepository(this._channel, this._username) {
    _channel.stream.listen((data) {
      _listenToServerHandler(data);
    });
  }

  static Future<DbRepository> init() async {
    final channel = WebSocketChannel.connect(Uri.parse("ws://$ipAddress:$wsPort"));

    final prefs = await SharedPreferences.getInstance();
    final username = prefs.getString(usernameKey) ?? '';

    return DbRepository(channel, username);
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

  String getUsername() => _username;

  void setUsername(String username) async {
    final prefs = await SharedPreferences.getInstance();
    prefs.setString(usernameKey, username);
    _username = username;
    notifyListeners();
  }

  Future<bool> checkOnline() async {
    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/documents/test")
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

  WebSocketChannel getWSChannel() {
    return _channel;
  }

  Future<Pair> getAllDocumentsForUser(String owner) async {
    _online = false;
    final url = "http://$ipAddress:$httpPort/documents/$owner";

    try {
      var response = await http
          .get(url)
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _localDocuments = rawRes.map((json) => Document.fromJson(json)).toList().cast<Document>();

        return Pair(Pair(_localDocuments, "ok"), _online);
      } else {
        return Pair(Pair(_localDocuments, response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_localDocuments, "ok"), _online);
  }

  Future<Pair> getAllDocuments() async {
    _online = false;
    const url = "http://$ipAddress:$httpPort/all";

    try {
      var response = await http
          .get(url)
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _localDocuments = rawRes.map((json) => Document.fromJson(json)).toList().cast<Document>();

        return Pair(Pair(_localDocuments, "ok"), _online);
      } else {
        return Pair(Pair(_localDocuments, response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_localDocuments, "ok"), _online);
  }

  Future<Pair> addDocument(String name, String status, String owner, int size, int usage) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/document",
          headers: headers,
          body: jsonEncode({
            'name': name,
            'status': status,
            'owner': owner,
            'size': size,
            'usage': usage
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

  Future<Pair> deleteDocument(int id) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .delete("http://$ipAddress:$httpPort/document/$id")
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

  Future<Pair> getTopDocumentsByUsage() async {
    var pairRepoRes = await getAllDocuments();
    var allDocs = pairRepoRes.left.left as List<Document>;
    var isOnline = pairRepoRes.right;

    allDocs.sort((e1, e2) =>
      e2.usage.compareTo(e1.usage)
    );

    var listRes = allDocs.take(10).toList();
    return Pair(listRes, isOnline);
  }
}
