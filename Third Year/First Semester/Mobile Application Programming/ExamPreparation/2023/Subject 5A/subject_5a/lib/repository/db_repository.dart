// ignore_for_file: import_of_legacy_library_into_null_safe

import 'dart:async';
import 'dart:collection';
import 'dart:convert';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

import '../domain/genre.dart';
import '../domain/movie.dart';
import '../utils/pair.dart';
import 'package:http/http.dart' as http;

class DbRepository extends ChangeNotifier {
  final WebSocketChannel _channel;

  bool _online = false;

  List<Genre> _localGenres = [];
  List<Movie> _allMovies = [];
  final Map<String, List<Movie>> _genreToMovies = {};

  static const String ipAddress = '10.152.1.86';
  static const String wsPort = '2305';
  static const String httpPort = '2305';

  static const String httpGetGenres = 'genres';
  static const String httpGetMoviesWithGenre = 'movies';
  static const String httpPostDeleteMovie = 'movie';
  static const String httpGetAllMovies = 'all';

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
          .get("http://$ipAddress:$httpPort/$httpGetGenres")
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

  Future<Pair> getAllGenres() async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetGenres")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _localGenres = rawRes.map((str) => Genre(str)).toList().cast<Genre>();

        return Pair(Pair(_localGenres, "ok"), _online);
      } else {
        return Pair(Pair(_localGenres, response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_localGenres, "ok"), _online);
  }

  Future<Pair> getMoviesWithGenre(String genre) async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetMoviesWithGenre/$genre")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);
        _genreToMovies[genre] = rawRes.map((json) => Movie.fromJson(json)).toList().cast<Movie>();

        return Pair(Pair(_genreToMovies[genre], "ok"), _online);
      } else {
        return Pair(Pair(_genreToMovies[genre], response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_genreToMovies[genre], "ok"), _online);
  }

  Future<Pair> addMovie(String name, String description, String genre, String director, int year) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .post("http://$ipAddress:$httpPort/$httpPostDeleteMovie",
          headers: headers,
          body: jsonEncode({
            'name': name,
            'description': description,
            'genre': genre,
            'director': director,
            'year': year
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

  Future<Pair> deleteMovie(int id) async {
    try {
      Map<String, String> headers = HashMap();
      headers['Accept'] = 'application/json';
      headers['Content-type'] = 'application/json';

      var response = await http
          .delete("http://$ipAddress:$httpPort/$httpPostDeleteMovie/$id")
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

  Future<Pair> getAllMovies() async {
    _online = false;

    try {
      var response = await http
          .get("http://$ipAddress:$httpPort/$httpGetAllMovies")
          .timeout(const Duration(seconds: 1));

      if (response.statusCode == 200) {
        _online = true;

        var rawRes = json.decode(response.body);

        // TODO: update the genreToMovie hashmap as well
        _allMovies = rawRes.map((json) => Movie.fromJson(json)).toList().cast<Movie>();

        return Pair(Pair(_allMovies, "ok"), _online);
      } else {
        return Pair(Pair(_allMovies, response.body), _online);
      }
    } on Exception {
      _online = false;
    }

    return Pair(Pair(_allMovies, "ok"), _online);
  }

  Future<Pair> getActiveYearsList() async {
    var pairRepoRes = await getAllMovies();
    var allMovies = pairRepoRes.left.left as List<Movie>;
    var isOnline = pairRepoRes.right;

    final Map<int, int> yearToMoviesNo = {};
    for(var i = 0; i < allMovies.length; ++i) {
      yearToMoviesNo.update(
        allMovies[i].year,
        (value) => ++value,
        ifAbsent: () => 1,
      );
    }

    var years = yearToMoviesNo.keys.toList();
    years.sort((y1, y2) => ((yearToMoviesNo[y1] ?? 0) < (yearToMoviesNo[y2] ?? 0)) ? 1 : 0);
    var listRes = years.map((year) => Pair(year, yearToMoviesNo[year] ?? 0)).toList();

    return Pair(listRes, isOnline);
  }

  Future<Pair> getMostPopularGenresList() async {
    var pairRepoRes = await getAllMovies();
    var allMovies = pairRepoRes.left.left as List<Movie>;
    var isOnline = pairRepoRes.right;

    final Map<String, int> genreToMoviesNo = {};
    for(var i = 0; i < allMovies.length; ++i) {
      genreToMoviesNo.update(
        allMovies[i].genre,
            (value) => ++value,
        ifAbsent: () => 1,
      );
    }

    var genres = genreToMoviesNo.keys.toList();
    genres.sort((y1, y2) => ((genreToMoviesNo[y1] ?? 0) < (genreToMoviesNo[y2] ?? 0)) ? 1 : 0);
    var listRes = genres.map((genre) => Pair(genre, genreToMoviesNo[genre] ?? 0)).take(3).toList();
  
    return Pair(listRes, isOnline);
  }

  WebSocketChannel getWSChannel() {
    return _channel;
  }
}
