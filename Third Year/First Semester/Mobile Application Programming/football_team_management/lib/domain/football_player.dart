class FootballPlayer {
  late int id;
  String name;
  String position;
  int number;
  int height;
  double weight;

  FootballPlayer(this.name, this.position, this.number, this.height, this.weight) {
    id = -1;
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'position': position,
      'number': number,
      'height': height,
      'weight': weight
    };
  }

  Map<String, dynamic> toMapWithId() {
    return {
      'id': id,
      'name': name,
      'position': position,
      'number': number,
      'height': height,
      'weight': weight
    };
  }

  factory FootballPlayer.fromJson(dynamic json) {
    var player = FootballPlayer(json['name'], json['position'], json['number'], json['height'], json['weight']);

    player.id = json['id'];

    return player;
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'position': position,
      'number': number,
      'height': height,
      'weight': weight
    };
  }
}
