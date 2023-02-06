import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../domain/document.dart';
import '../repository/db_repository.dart';
import '../utils/Utils.dart';

class DeleteDocumentSection extends StatefulWidget {
  final Document _document;

  const DeleteDocumentSection(this._document, {Key? key}) : super(key: key);

  @override
  State<DeleteDocumentSection> createState() => _DeleteDocumentSection();
}

class _DeleteDocumentSection extends State<DeleteDocumentSection> {
  bool isDeleteLoading = false;

  void showAreYouSureDialog() {
    // set up the button
    Widget yesButton = TextButton(
        child: const Text("Yes"),
        onPressed: () async {
          setState(() {
            isDeleteLoading = true;
          });

          var result = await Provider.of<DbRepository>(context, listen: false).deleteDocument(
              widget._document.id
          );

          setState(() {
            isDeleteLoading = false;
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
            Utils.showAlertDialog(context, "Delete is not possible while offline!");
          }
        }
    );

    Widget cancelButton = TextButton(
      child: const Text("Cancel"),
      onPressed: () {
        Navigator.pop(context);
      },
    );

    // set up the AlertDialog
    AlertDialog alert = AlertDialog(
      title: const Text("Error"),
      content: const Text('Are you sure you want to remove this entity?'),
      actions: [
        cancelButton,
        yesButton,
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
    nameController.text = widget._document.name;

    var statusController = TextEditingController();
    statusController.text = widget._document.status;

    var ownerController = TextEditingController();
    ownerController.text = widget._document.owner;

    var sizeController = TextEditingController();
    sizeController.text = widget._document.size.toString();

    var usageController = TextEditingController();
    usageController.text = widget._document.usage.toString();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Delete document'),
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
                      controller: statusController,
                      decoration: const InputDecoration(
                        labelText: "Status",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: ownerController,
                      decoration: const InputDecoration(
                        labelText: "Owner",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: sizeController,
                      decoration: const InputDecoration(
                        labelText: "Size",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: usageController,
                      decoration: const InputDecoration(
                        labelText: "Usage",
                      ))),
              Center(
                child: !isDeleteLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Delete document"),
                      ],
                    ),
                  ),
                  onPressed: () {
                    showAreYouSureDialog();
                  },
                ) : const Center(child:CircularProgressIndicator()),
              ),
            ],
          ),
        )
    );
  }
}
