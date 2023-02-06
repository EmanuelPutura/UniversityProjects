import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_2b/utils/http_out_message.dart';

import '../persistence/db_repository.dart';
import '../utils/utils.dart';

class AddActivitySection extends StatefulWidget {
  const AddActivitySection({Key? key}) : super(key: key);

  @override
  State<AddActivitySection> createState() => _AddActivitySection();
}

class _AddActivitySection extends State<AddActivitySection> {
  bool isLoading = false;

  @override
  Widget build(BuildContext context) {
    var nameController = TextEditingController();
    var descriptionController = TextEditingController();
    var categoryController = TextEditingController();
    var dateController = TextEditingController();
    var timeController = TextEditingController();
    var intensityController = TextEditingController();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Add activity'),
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
                      controller: categoryController,
                      decoration: const InputDecoration(
                        labelText: "Category",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: dateController,
                      decoration: const InputDecoration(
                        labelText: "Date",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: timeController,
                      decoration: const InputDecoration(
                        labelText: "Time",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
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
                        Text("Add activity"),
                      ],
                    ),
                  ),
                  onPressed: () async {
                    setState(() {
                      isLoading = true;
                    });

                    final dateDateTime = DateTime.tryParse(dateController.text);
                    final timeInt = int.tryParse(timeController.text);

                    if (dateDateTime == null || timeInt == null) {
                      Utils.showAlertDialog(context, 'The provided entity details are invalid!');
                      isLoading = false;
                      return;
                    }

                    var httpOutMessage = await Provider.of<DbRepository>(context, listen: false).addActivity(
                        nameController.text,
                        descriptionController.text,
                        categoryController.text,
                        dateDateTime,
                        timeInt,
                        intensityController.text
                    );

                    setState(() {
                      isLoading = false;
                    });

                    final serverResponse = httpOutMessage.serverResponse;
                    final online = httpOutMessage.online;

                    if (!mounted) {
                      return;
                    }

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
