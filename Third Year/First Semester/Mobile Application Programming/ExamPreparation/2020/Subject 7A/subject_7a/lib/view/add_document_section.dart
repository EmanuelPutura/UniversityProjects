import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../repository/db_repository.dart';
import '../utils/Utils.dart';

class AddDocumentSection extends StatefulWidget {
  const AddDocumentSection({Key? key}) : super(key: key);

  @override
  State<AddDocumentSection> createState() => _AddDocumentSection();
}

class _AddDocumentSection extends State<AddDocumentSection> {
  bool isAddLoading = false;

  @override
  Widget build(BuildContext context) {
    var nameController = TextEditingController();
    var statusController = TextEditingController();
    var sizeController = TextEditingController();
    var usageController = TextEditingController();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Add document'),
        ),
        body: SingleChildScrollView(
          child: Column(
            children: [
              ListTile(
                  leading: const Icon(Icons.person),
                  title: TextField(
                      controller: nameController,
                      decoration: const InputDecoration(
                        labelText: "Name",
                      ))),
              ListTile(
                  leading: const Icon(Icons.add_location_alt_outlined),
                  title: TextField(
                      controller: statusController,
                      decoration: const InputDecoration(
                        labelText: "Status",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      controller: sizeController,
                      decoration: const InputDecoration(
                        labelText: "Size",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: usageController,
                      decoration: const InputDecoration(
                        labelText: "Usage",
                      ))),
              Center(
                child: !isAddLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Add document"),
                      ],
                    ),
                  ),
                  onPressed: () async {
                    setState(() {
                      isAddLoading = true;
                    });

                    var sizeInt = int.tryParse(sizeController.text);
                    var usageInt = int.tryParse(usageController.text);

                    if (sizeInt == null || usageInt == null) {
                      isAddLoading = false;
                      Utils.showAlertDialog(context, 'The provided entity details are invalid!');
                      return;
                    }

                    final username = Provider.of<DbRepository>(context, listen: false).getUsername();

                    var result = await Provider.of<DbRepository>(context, listen: false).addDocument(
                        nameController.text,
                        statusController.text,
                        username,
                        sizeInt,
                        usageInt
                    );

                    setState(() {
                      isAddLoading = false;
                    });

                    if (result.left is String && result.left != "ok") {
                      final snackBar = SnackBar(
                        content: Text(result.left as String),
                      );

                      ScaffoldMessenger.of(context).showSnackBar(snackBar);
                      return;
                    }

                    if (result.right is bool && result.right) {
                      Navigator.pop(context);
                    }
                    else {
                      Utils.showAlertDialog(context, "Add is not possible while offline!");
                    }
                  },
                ) : const Center(child:CircularProgressIndicator()),
              ),
            ],
          ),
        )
    );
  }
}
