class Genre {
  String name;

  Genre(this.name);

  Map<String, dynamic> toMap() {
    return {
      'name': name
    };
  }

  factory Genre.fromJson(dynamic json) {
    return Genre(json['name']);
  }

  Map<String, dynamic> toJson() {
    return {
      'name': name
    };
  }
}
