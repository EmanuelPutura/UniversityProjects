import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_7a/view/top_documents_list_widget.dart';
import '../repository/db_repository.dart';

class StatusSection extends StatefulWidget {
  const StatusSection({Key? key}) : super(key: key);

  @override
  State<StatusSection> createState() => _StatusSection();
}

class _StatusSection extends State<StatusSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Status section'),
        ),
        body: const TopDocumentsListWidget(),
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
