class FootballPlayer {
  static int _currentId = 0;

  late int id;
  String name;
  String position;
  int number;
  int height;
  double weight;

  FootballPlayer(this.name, this.position, this.number, this.height, this.weight) {
    id = ++_currentId;
  }
}
