import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_7a/view/all_documents_list_widget.dart';
import '../repository/db_repository.dart';

class ManageSection extends StatefulWidget {
  const ManageSection({Key? key}) : super(key: key);

  @override
  State<ManageSection> createState() => _ManageSection();
}

class _ManageSection extends State<ManageSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Manage section'),
        ),
        body: const AllDocumentsListWidget(),
        floatingActionButton: Container(
            alignment: Alignment.bottomCenter,
            child: ElevatedButton(
              onPressed: () {
                Provider.of<DbRepository>(context, listen: false).checkOnline();
              },
              child: const Text("Refresh"),
            ),
        )
    );
  }
}
