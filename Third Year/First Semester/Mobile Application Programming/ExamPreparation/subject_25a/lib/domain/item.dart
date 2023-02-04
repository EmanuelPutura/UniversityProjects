class Item {
  late int id;
  String name;
  String description;
  String image;
  String category;
  int units;
  num price;

  Item(this.name, this.description, this.image, this.category, this.units, this.price) {
    id = -1;
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'description': description,
      'image': image,
      'category': category,
      'units': units,
      'price': price
    };
  }

  Map<String, dynamic> toMapWithId() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'image': image,
      'category': category,
      'units': units,
      'price': price
    };
  }

  factory Item.fromJson(dynamic json) {
    var entity = Item(json['name'], json['description'], json['image'], json['category'], json['units'], json['price']);
    entity.id = json['id'];

    return entity;
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'image': image,
      'category': category,
      'units': units,
      'price': price
    };
  }
}
