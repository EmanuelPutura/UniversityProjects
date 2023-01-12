import 'package:animal_shelter/pair.dart';
import 'package:flutter/cupertino.dart';

import 'animal.dart';
import 'animal_repository.dart';

class AnimalService extends ChangeNotifier {
  final AnimalRepository _animal_repo;

  AnimalService(this._animal_repo);

  static Future<AnimalService> init() async {
    var repo = await AnimalRepository.init();
    return AnimalService(repo);
  }

  Future<void> add(
      String name, int age, String breed, String description) async {
    _animal_repo.addAnimal(name, age, breed, description);

    notifyListeners();
  }

  Future<String> remove(int id) async {
    var res = _animal_repo.removeAnimal(id);

    notifyListeners();

    return res;
  }

  Future<String> update(int id, String newName, int newAge, String newBreed,
      String newDescription) async {
    var res = _animal_repo.updateAnimal(id, newName, newAge, newBreed, newDescription);

    notifyListeners();

    return res;
  }

  Future<Pair> getAll() async {
    return await _animal_repo.getAnimals();
  }
}
