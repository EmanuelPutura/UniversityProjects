import 'dart:ffi';

class Animal {
    Animal(this.name, this.age, this.breed, this.description) {
        id = -1;
    }

    late int id;
    String name;
    int age;
    String breed;
    String description;

    Map<String, dynamic> toMap() {
        return {
            'name': name,
            'age': age,
            'breed': breed,
            'description': description
        };
    }

    Map<String, dynamic> toMapWithId() {
        return {
            'id': id,
            'name': name,
            'age': age,
            'breed': breed,
            'description': description
        };
    }

    factory Animal.fromJson(dynamic json) {
        var animal = Animal(json['name'], json['age'], json['breed'], json['description']);

        animal.id = json['id'];

        return animal;
    }

    Map toJson() {
        return {
            'id': id,
            'name': name,
            'age': age,
            'breed': breed,
            'description': description
        };
    }
}