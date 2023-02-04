import 'dart:math';

import 'package:flutter/cupertino.dart';
import 'package:subject_25a/repository/db_repository.dart';

import '../domain/item.dart';
import '../utils/pair.dart';

class MainService extends ChangeNotifier {
  final DatabaseRepository _repository;

  MainService(this._repository);

  static Future<MainService> init() async {
    var repository = await DatabaseRepository.init();
    return MainService(repository);
  }

  Future<Pair> getAllCategories() async {
    return await _repository.getAllCategories();
  }

  Future<Pair> getItemsWithCategory(String category) async {
    return await _repository.getItemsWithCategory(category);
  }

  Future<bool> addItem(String name, String description, String image, String category, int units, num price) async {
    var result = await _repository.addItem(Item(name, description, image, category, units, price));
    notifyListeners();
    return result;
  }

  Future<bool> checkOnline() async {
    var result = await _repository.checkOnline();
    notifyListeners();
    return result;
  }
}
