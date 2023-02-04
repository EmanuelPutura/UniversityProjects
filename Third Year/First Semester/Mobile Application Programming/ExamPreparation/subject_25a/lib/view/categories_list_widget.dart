import 'package:flutter/material.dart';
import 'package:subject_25a/view/price_section.dart';
import 'package:provider/provider.dart';
import '../service/main_service.dart';
import '../utils/pair.dart';
import 'category_items_section.dart';

class CategoriesListWidget extends StatefulWidget {
  const CategoriesListWidget({Key? key}) : super(key: key);

  @override
  State<CategoriesListWidget> createState() => _CategoriesListWidget();
}

class _CategoriesListWidget extends State<CategoriesListWidget> {
  Widget _buildListView() {
    var entitiesFuture = Provider.of<MainService>(context, listen: true).getAllCategories();

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
          if (entities?.left.length == 0) {
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
              itemCount: entities?.left.length,
              shrinkWrap: true,
              itemBuilder: (context, index) {
                var entity = entities?.left[index];

                if (entities?.left != [] && entity == null) {
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
                      ],
                    ),

                    onTap: () => {
                      Navigator.of(context).push(
                          MaterialPageRoute<void>(
                              builder: (context) {
                                return CategoryItemsSection(entity.name);
                              }
                          )
                      )
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
    return _buildListView();
  }
}
