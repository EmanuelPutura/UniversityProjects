import 'package:flutter/material.dart';
import 'package:football_team_management/view/home_page.dart';
import 'package:provider/provider.dart';
import '../service/football_players_service.dart';

class FootballPlayerDetailsWidget extends StatefulWidget {
  final int index;

  const FootballPlayerDetailsWidget(this.index, {Key? key}) : super(key: key);

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
        var player = Provider.of<FootballPlayersService>(context, listen: false)
            .getAllPlayers()[widget.index];

        Provider.of<FootballPlayersService>(context, listen: false).remove(player.id);
        Navigator.of(context).push(
            MaterialPageRoute<void>(
                builder: (context) {
                  return const HomePageWidget();
                }
            )
        );
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
    var player = Provider.of<FootballPlayersService>(context, listen: true)
        .getAllPlayers()[widget.index];

    var nameController = TextEditingController(text: player.name);
    var positionController = TextEditingController(text: player.position);
    var numberController =
    TextEditingController(text: player.number.toString());
    var heightController =
    TextEditingController(text: player.height.toString());
    var weightController =
    TextEditingController(text: player.weight.toString());

    return Scaffold(
      appBar: AppBar(
        centerTitle: true,
        title: Text(player.name),
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

                  Provider.of<FootballPlayersService>(context, listen: false)
                      .update(
                      player.id,
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
                  var wasCancelled = showAreYouSureDialog();
                },
              ),
            )
          ],
        ),
      )
    );
  }
}

