import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../repository/db_repository.dart';

class AddItemSection extends StatefulWidget {
  final String _category;

  const AddItemSection(this._category, {Key? key}) : super(key: key);

  @override
  State<AddItemSection> createState() => _AddItemSection();
}

class _AddItemSection extends State<AddItemSection> {
  bool isAddLoading = false;

  void showAlertDialog(BuildContext context, String message) {
    // set up the button
    Widget okButton = TextButton(
      child: const Text("OK"),
      onPressed: () {
        Navigator.pop(context);
      },
    );

    // set up the AlertDialog
    AlertDialog alert = AlertDialog(
      title: const Text("Error"),
      content: Text(message),
      actions: [
        okButton,
      ],
    );

    // show the dialog
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return alert;
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    var nameController = TextEditingController();
    var descriptionController = TextEditingController();
    var imageController = TextEditingController();
    var unitsController = TextEditingController();
    var priceController = TextEditingController();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Add item'),
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
                      controller: descriptionController,
                      decoration: const InputDecoration(
                        labelText: "Description",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      controller: imageController,
                      decoration: const InputDecoration(
                        labelText: "Image",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: unitsController,
                      decoration: const InputDecoration(
                        labelText: "Units",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: priceController,
                      decoration: const InputDecoration(
                        labelText: "Price",
                      ))),
              Center(
                child: !isAddLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Add item"),
                      ],
                    ),
                  ),
                  onPressed: () async {
                    setState(() {
                      isAddLoading = true;
                    });

                    var unitsInt = int.tryParse(unitsController.text);
                    var priceNum = num.tryParse(priceController.text);

                    if (unitsInt == null || priceNum == null) {
                      showAlertDialog(context, 'The provided entity details are invalid!');
                      return;
                    }

                    var result = await Provider.of<DbRepository>(context, listen: false).addItem(
                        nameController.text,
                        descriptionController.text,
                        imageController.text,
                        widget._category,
                        unitsInt,
                        priceNum
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
                      showAlertDialog(context, "Add is not possible while offline!");
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
