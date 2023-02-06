import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../repository/db_repository.dart';
import '../utils/pair.dart';

class OwnerDocumentsListWidget extends StatefulWidget {
  const OwnerDocumentsListWidget({Key? key}) : super(key: key);

  @override
  State<OwnerDocumentsListWidget> createState() => _OwnerDocumentsListWidget();
}

class _OwnerDocumentsListWidget extends State<OwnerDocumentsListWidget> {
  Widget _buildListView() {
    var username = Provider.of<DbRepository>(context, listen: true).getUsername();
    var entitiesFuture = Provider.of<DbRepository>(context, listen: true).getAllDocumentsForUser(username);

    return FutureBuilder<Pair>(
        future: entitiesFuture,
        builder: (context, snapshot) {
          switch (snapshot.connectionState) {
            case ConnectionState.none:
              return const Text('None');
            case ConnectionState.waiting:
              return const Center(child: CircularProgressIndicator());
            case ConnectionState.active:
              return const Text('Active');
            case ConnectionState.done:
              if (snapshot.hasError) {
                return Text(
                  '${snapshot.error}',
                  style: const TextStyle(color: Colors.red),
                );
              }
          }

          var entities = snapshot.data;
          if (entities?.left?.left.length == 0) {
            return Card(
                shape: RoundedRectangleBorder(
                  side: BorderSide(
                    color: Colors.blue.shade300,
                  ),
                  borderRadius: BorderRadius.circular(15.0),
                ),
                child: const Text("Offline")
            );
          }

          return ListView.builder(
              itemCount: entities?.left.left.length,
              shrinkWrap: true,
              itemBuilder: (context, index) {
                var entity = entities?.left.left[index];

                if (entities?.left.left != [] && entity == null) {
                  return const Card();
                }
                else if (entity == null && index == 0) {
                  return const Card(
                      child: Text("Offline")
                  );
                }
                else if (entity == null) {
                  return const Card();
                }

                var card = Card(
                  shape: RoundedRectangleBorder(
                    side: BorderSide(
                      color: Colors.blue.shade300,
                    ),
                    borderRadius: BorderRadius.circular(15.0),
                  ),
                  child: ListTile(
                      title: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: <Widget>[
                          Text(
                            entity.name,
                            style: const TextStyle(
                                color: Colors.black,
                                fontSize: 19.0,
                                fontWeight: FontWeight.bold),
                          ),
                          Text(
                            entity.status,
                            style: const TextStyle(
                                color: Colors.black,
                                fontSize: 19.0,
                                fontWeight: FontWeight.bold),
                          ),
                          Text(
                            entity.owner,
                            style: const TextStyle(
                                color: Colors.black,
                                fontSize: 19.0,
                                fontWeight: FontWeight.bold),
                          ),
                          Text(
                            entity.size.toString(),
                            style: const TextStyle(
                                color: Colors.black,
                                fontSize: 19.0,
                                fontWeight: FontWeight.bold),
                          ),
                        ],
                      ),

                      onTap: () => {
                      }
                  ),
                );

                if (entities?.right == false && index == 0) {
                  return Card(
                    child: Column(
                        children: [
                          const Text("Offline"),
                          card
                        ]
                    ),
                  );
                }

                return card;
              }
          );
        }
    );
  }

  @override
  Widget build(BuildContext context) {
    final storage = Provider.of<DbRepository>(context);
    final infoMessage = storage.getInfoMessage();

    if (infoMessage != '') {
      return AlertDialog(
        title: const Text('Alert'),
        content: SingleChildScrollView(
          child: ListBody(
            children: <Widget>[
              Text(infoMessage)
            ],
          ),
        ),
        actions: [
          TextButton(
            child: const Text("OK"),
            onPressed: () {
              storage.setInfoMessage('');
            },
          )
        ],
      );
    }

    return _buildListView();
  }
}
