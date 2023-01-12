import 'package:flutter/material.dart';
import 'package:football_team_management/domain/football_player.dart';
import 'package:provider/provider.dart';

import '../service/football_players_service.dart';
import 'home_page.dart';

class FootballPlayerDetailsWidget extends StatefulWidget {
  final FootballPlayer _player;

  const FootballPlayerDetailsWidget(this._player, {Key? key}) : super(key: key);

  @override
  State<FootballPlayerDetailsWidget> createState() => _FootballPlayerDetailsWidgetState();
}

class _FootballPlayerDetailsWidgetState extends State<FootballPlayerDetailsWidget> {
  _FootballPlayerDetailsWidgetState();

  void showAlertDialog(String message) {
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

  bool showAreYouSureDialog() {
    bool isCancelled = false;

    // set up the button
    Widget yesButton = TextButton(
      child: const Text("Yes"),
      onPressed: () {
        var res = Provider.of<FootballPlayersService>(context, listen: false).remove(widget._player.id);
        res.then((value) => {
          if (value == "SUCCESS") {
            Navigator.of(context).push(
                MaterialPageRoute<void>(
                    builder: (context) {
                      return const HomePageWidget();
                    }
                )
            )
          }
          else {
            showDialog(
                context: context,
                builder: (BuildContext context) {
                  return AlertDialog(
                    title: const Text("Error"),
                    content: const Text("You are offline or there was an error, try to connect again."),
                    actions: [
                      ElevatedButton(
                          onPressed: () {
                            Navigator.of(context).push(MaterialPageRoute(builder: (context) => const HomePageWidget()));
                          },
                          child: const Text("OK")
                      )
                    ],
                  );
                }
            )
          }
        });

        // Navigator.of(context).push(
        //     MaterialPageRoute<void>(
        //         builder: (context) {
        //           return const HomePageWidget();
        //         }
        //     )
        // );
      },
    );

    Widget cancelButton = TextButton(
      child: const Text("Cancel"),
      onPressed: () {
        isCancelled = true;
        Navigator.pop(context);
      },
    );

    // set up the AlertDialog
    AlertDialog alert = AlertDialog(
      title: const Text("Error"),
      content: const Text('Are you sure you want to remove this player from the team?'),
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

    return isCancelled;
  }

  @override
  Widget build(BuildContext context) {
    var nameController = TextEditingController(text: widget._player.name);
    var positionController = TextEditingController(text: widget._player.position);
    var numberController =
    TextEditingController(text: widget._player.number.toString());
    var heightController =
    TextEditingController(text: widget._player.height.toString());
    var weightController =
    TextEditingController(text: widget._player.weight.toString());

    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Text(widget._player.name),
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
                      Text("Update player"),
                    ],
                  ),
                ),
                onPressed: () {
                  var numberStr = int.tryParse(numberController.text);
                  var heightStr = int.tryParse(heightController.text);
                  var weightStr = double.tryParse(weightController.text);

                  if (numberStr == null || heightStr == null || weightStr == null) {
                    showAlertDialog('The provided player details are invalid!');
                    return;
                  }

                  var res = Provider.of<FootballPlayersService>(context, listen: false)
                      .update(
                      widget._player.id,
                      nameController.text,
                      positionController.text,
                      numberStr,
                      heightStr,
                      weightStr
                  );

                  res.then((value) => {
                    if (value == "SUCCESS") {
                      Navigator.pop(context)
                    }
                    else {
                      showDialog(
                          context: context,
                          builder: (BuildContext context) {
                            return AlertDialog(
                              title: const Text("Error"),
                              content: const Text("You are offline or there was an error, try to connect again."),
                              actions: [
                                ElevatedButton(
                                    onPressed: () {
                                      Navigator.of(context).push(MaterialPageRoute(builder: (context) => const HomePageWidget()));
                                    },
                                    child: const Text("OK")
                                )
                              ],
                            );
                          }
                      )
                    }
                  });

                  // Navigator.pop(context);
                },
              ),
            ),
            Center(
              child: ElevatedButton(
                child: SizedBox(
                  width: MediaQuery.of(context).size.width / 2,
                  child: Column(
                    mainAxisSize: MainAxisSize.min,
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: const [
                      Text("Delete player"),
                    ],
                  ),
                ),
                onPressed: () {
                  showAreYouSureDialog();
                },
              ),
            )
          ],
        ),
      )
    );
  }
}
