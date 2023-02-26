import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../../persistence/db_repository.dart';
import '../../utils/http_out_message.dart';

class ProgressListWidget extends StatefulWidget {
  const ProgressListWidget({Key? key}) : super(key: key);

  @override
  State<ProgressListWidget> createState() => _ProgressListWidget();
}

class _ProgressListWidget extends State<ProgressListWidget> {
  Widget _buildListView() {
    var httpOutMessageFuture = Provider.of<DbRepository>(context, listen: true).getTotalAmountPerWeek();

    return FutureBuilder<HttpOutMessage<List<MapEntry<String, num>>>>(
        future: httpOutMessageFuture,
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

          final httpOutMessage = snapshot.data;
          if (httpOutMessage == null) {
            return Card(
                shape: RoundedRectangleBorder(
                  side: BorderSide(
                    color: Colors.blue.shade300,
                  ),
                  borderRadius: BorderRadius.circular(15.0),
                ),
                child: const Text("Error: null persistence return value!")
            );
          }

          final entities = httpOutMessage.collection;
          final online = httpOutMessage.online;

          if (entities.isEmpty) {
            final text = online ? "Empty list" : "Offline";

            return Card(
                shape: RoundedRectangleBorder(
                  side: BorderSide(
                    color: Colors.blue.shade300,
                  ),
                  borderRadius: BorderRadius.circular(15.0),
                ),
                child: Text(text)
            );
          }

          return ListView.builder(
              itemCount: entities.length,
              shrinkWrap: true,
              itemBuilder: (context, index) {
                var entity = entities[index];

                if (!online && index == 0) {
                  return const Card(
                      child: Text("Offline")
                  );
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
                            entity.key,
                            style: const TextStyle(
                                color: Colors.black,
                                fontSize: 19.0,
                                fontWeight: FontWeight.bold),
                          ),
                          Text(
                            entity.value.toString(),
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

                if (online == false && index == 0) {
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
