class Category {
  String name;

  Category(this.name);

  Map<String, dynamic> toMap() {
    return {
      'name': name
    };
  }

  factory Category.fromJson(dynamic json) {
    return Category(json['name']);
  }

  Map<String, dynamic> toJson() {
    return {
      'name': name
    };
  }
}
