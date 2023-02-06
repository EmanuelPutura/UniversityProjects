import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_2b/utils/http_out_message.dart';

import '../domain/activity.dart';
import '../persistence/db_repository.dart';
import '../utils/utils.dart';

class DeleteActivitySection extends StatefulWidget {
  final Activity _activity;

  const DeleteActivitySection(this._activity, {Key? key}) : super(key: key);

  @override
  State<DeleteActivitySection> createState() => _DeleteActivitySection();
}

class _DeleteActivitySection extends State<DeleteActivitySection> {
  bool isLoading = false;

  void showAreYouSureDialog() {
    // set up the button
    Widget yesButton = TextButton(
        child: const Text("Yes"),
        onPressed: () async {
          setState(() {
            isLoading = true;
          });

          var httpOutMessage = await Provider.of<DbRepository>(context, listen: false).deleteActivity(
              widget._activity.id
          );

          setState(() {
            isLoading = false;
          });

          if (!mounted) {
            return;
          }

          final serverResponse = httpOutMessage.serverResponse;
          final online = httpOutMessage.online;

          if (serverResponse != HttpOutMessage.okServerMessage) {
            final snackBar = SnackBar(
              content: Text(serverResponse),
            );

            ScaffoldMessenger.of(context).showSnackBar(snackBar);
            return;
          }

          if (online) {
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
    nameController.text = widget._activity.name;

    var descriptionController = TextEditingController();
    descriptionController.text = widget._activity.description;

    var categoryController = TextEditingController();
    categoryController.text = widget._activity.category;

    var dateController = TextEditingController();
    dateController.text = widget._activity.date.toIso8601String();

    var timeController = TextEditingController();
    timeController.text = widget._activity.time.toString();

    var intensityController = TextEditingController();
    intensityController.text = widget._activity.intensity;

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Delete activity'),
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
                      controller: categoryController,
                      decoration: const InputDecoration(
                        labelText: "Category",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: dateController,
                      decoration: const InputDecoration(
                        labelText: "Date",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: timeController,
                      decoration: const InputDecoration(
                        labelText: "Time",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: intensityController,
                      decoration: const InputDecoration(
                        labelText: "Intensity",
                      ))),
              Center(
                child: !isLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Delete activity"),
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
