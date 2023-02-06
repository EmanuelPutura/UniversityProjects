class Activity implements Comparable<Activity> {
  late int id;
  String name;
  String description;
  String category;
  DateTime date;
  int time;
  String intensity;

  Activity(this.name, this.description, this.category, this.date, this.time, this.intensity) {
    id = -1;
  }

  factory Activity.fromJson(dynamic json) {
    var entity = Activity(
        json['name'],
        json['description'],
        json['category'],
        DateTime.parse(json['date']),
        json['time'],
        json['intensity']
    );
    entity.id = json['id'];

    return entity;
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'description': description,
      'category': category,
      'date': date.toIso8601String(),
      'time': time,
      'intensity': intensity
    };
  }

  Map<String, dynamic> toJsonWithoutId() {
    return {
      'name': name,
      'description': description,
      'category': category,
      'date': date.toIso8601String(),
      'time': time,
      'intensity': intensity
    };
  }

  @override
  int compareTo(Activity other) {
    if (intensity.compareTo(other.intensity) > 0 || (intensity == other.intensity && category.compareTo(other.category) > 0)) {
      return 1;
    }

    if (id == other.id && name == other.name && description == other.description) {
      return 0;
    }

    return -1;
  }}
