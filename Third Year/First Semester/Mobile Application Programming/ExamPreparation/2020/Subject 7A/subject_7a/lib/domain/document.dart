class Document {
  late int id;
  String name;
  String status;
  String owner;
  int size;
  int usage;

  Document(this.name, this.status, this.owner, this.size, this.usage) {
    id = -1;
  }

  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'status': status,
      'owner': owner,
      'size': size,
      'usage': usage
    };
  }

  Map<String, dynamic> toMapWithId() {
    return {
      'id': id,
      'name': name,
      'status': status,
      'owner': owner,
      'size': size,
      'usage': usage
    };
  }

  factory Document.fromJson(dynamic json) {
    var entity = Document(
        json['name'],
        json['status'],
        json['owner'],
        json['size'],
        json['usage']
    );
    entity.id = json['id'];

    return entity;
  }

  Map<String, dynamic> toJson() {
    return {
      'id': id,
      'name': name,
      'status': status,
      'owner': owner,
      'size': size,
      'usage': usage
    };
  }
}
