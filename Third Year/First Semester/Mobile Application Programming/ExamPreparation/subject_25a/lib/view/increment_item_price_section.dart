import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../domain/item.dart';
import '../repository/db_repository.dart';

class IncrementItemPriceSection extends StatefulWidget {
  final Item _item;

  const IncrementItemPriceSection(this._item, {Key? key}) : super(key: key);

  @override
  State<IncrementItemPriceSection> createState() => _IncrementItemPriceSection();
}

class _IncrementItemPriceSection extends State<IncrementItemPriceSection> {
  bool isLoading = false;

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

    var nameController = TextEditingController();
    nameController.text = widget._item.name;

    var descriptionController = TextEditingController();
    descriptionController.text = widget._item.description;

    var imageController = TextEditingController();
    imageController.text = widget._item.image;

    var unitsController = TextEditingController();
    unitsController.text = widget._item.units.toString();

    var priceController = TextEditingController();
    priceController.text = widget._item.price.toString();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Increment price by 1 unit'),
        ),
        body: SingleChildScrollView(
          child: Column(
            children: [
              ListTile(
                  leading: const Icon(Icons.person),
                  title: TextField(
                      readOnly: true,
                      controller: nameController,
                      decoration: const InputDecoration(
                        labelText: "Name",
                      ))),
              ListTile(
                  leading: const Icon(Icons.add_location_alt_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: descriptionController,
                      decoration: const InputDecoration(
                        labelText: "Description",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: imageController,
                      decoration: const InputDecoration(
                        labelText: "Image",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: unitsController,
                      decoration: const InputDecoration(
                        labelText: "Units",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: priceController,
                      decoration: const InputDecoration(
                        labelText: "Price",
                      ))),
              Center(
                child: !isLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Increment price by 1 unit"),
                      ],
                    ),
                  ),
                  onPressed: () async {
                    setState(() {
                      isLoading = true;
                    });

                    var result = await Provider.of<DbRepository>(context, listen: false).incrementPrice(
                        widget._item.id,
                        widget._item.price + 1
                    );

                    setState(() {
                      isLoading = false;
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
                      showAlertDialog(context, "Update is not possible while offline!");
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
