import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_7a/view/manage_section.dart';
import 'package:subject_7a/view/owner_documents_list_widget.dart';
import 'package:subject_7a/view/status_section.dart';
import '../repository/db_repository.dart';
import 'add_document_section.dart';

class MainSection extends StatefulWidget {
  const MainSection({Key? key}) : super(key: key);

  @override
  State<MainSection> createState() => _MainSection();
}

class _MainSection extends State<MainSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Main section'),
        ),
        body: const OwnerDocumentsListWidget(),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Column(
            mainAxisAlignment: MainAxisAlignment.end,
            children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                const Spacer(),
                ElevatedButton(
                  onPressed: () {
                    Navigator.of(context)
                        .push(MaterialPageRoute(builder: (context) => const ManageSection()));
                  },
                  child: const Text('Manage section'),
                ),
                const Spacer(),
                ElevatedButton(
                  onPressed: () {
                    Navigator.of(context)
                        .push(MaterialPageRoute(builder: (context) => const StatusSection()));
                  },
                  child: const Text('Status section'),
                ),
                const Spacer(),
              ]
            ),
              Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    const Spacer(),
                    ElevatedButton(
                      onPressed: () {
                        Provider.of<DbRepository>(context, listen: false).checkOnline();
                      },
                      child: const Text("Refresh"),
                    ),
                    const Spacer(),
                    ElevatedButton(
                      onPressed: () {
                        Navigator.of(context)
                            .push(MaterialPageRoute(builder: (context) => const AddDocumentSection()));
                      },
                      child: const Text("Add document"),
                    ),
                    const Spacer(),
                  ]
              ),
            ],
          )
        )
    );
  }
}
