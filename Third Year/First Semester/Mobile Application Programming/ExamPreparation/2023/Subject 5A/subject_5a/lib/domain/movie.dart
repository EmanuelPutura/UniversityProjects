class Movie {
  late int id;
  String name;
  String description;
  String genre;
  String director;
  int year;

  Movie(this.name, this.description, this.genre, this.director, this.year) {
    id = -1;
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'description': description,
      'genre': genre,
      'director': director,
      'year': year
    };
  }

  Map<String, dynamic> toMapWithId() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'genre': genre,
      'director': director,
      'year': year
    };
  }

  factory Movie.fromJson(dynamic json) {
    var entity = Movie(
        json['name'],
        json['description'],
        json['genre'],
        json['director'],
        json['year']
    );
    entity.id = json['id'];

    return entity;
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'genre': genre,
      'director': director,
      'year': year
    };
  }
}
