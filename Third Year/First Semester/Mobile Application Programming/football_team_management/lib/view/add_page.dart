import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../service/football_players_service.dart';

class FootballPlayerAddPage extends StatelessWidget {
  const FootballPlayerAddPage({Key? key}) : super(key: key);

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
    var positionController = TextEditingController();
    var numberController = TextEditingController();
    var heightController = TextEditingController();
    var weightController = TextEditingController();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Add player'),
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
                      controller: positionController,
                      decoration: const InputDecoration(
                        labelText: "Field Position",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      controller: numberController,
                      decoration: const InputDecoration(
                        labelText: "Number",
                      ))),
              ListTile(
                  leading: const Icon(Icons.local_library_outlined),
                  title: TextField(
                      controller: heightController,
                      decoration: const InputDecoration(
                        labelText: "Height",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: weightController,
                      decoration: const InputDecoration(
                        labelText: "Weight",
                      ))),
              Center(
                child: ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Add player"),
                      ],
                    ),
                  ),
                  onPressed: () {
                    var numberStr = int.tryParse(numberController.text);
                    var heightStr = int.tryParse(heightController.text);
                    var weightStr = double.tryParse(weightController.text);

                    if (numberStr == null || heightStr == null || weightStr == null) {
                      showAlertDialog(context, 'The provided player details are invalid!');
                      return;
                    }

                    Provider.of<FootballPlayersService>(context, listen: false)
                        .add(
                        nameController.text,
                        positionController.text,
                        numberStr,
                        heightStr,
                        weightStr
                    );

                    Navigator.pop(context);
                  },
                ),
              ),
            ],
          ),
        )
    );
  }
}
