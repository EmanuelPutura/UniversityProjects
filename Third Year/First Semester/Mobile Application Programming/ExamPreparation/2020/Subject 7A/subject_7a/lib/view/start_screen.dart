import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_7a/utils/utils.dart';
import 'package:subject_7a/view/main_section.dart';

import '../repository/db_repository.dart';

class StartScreen extends StatefulWidget {
  const StartScreen({Key? key}) : super(key: key);

  @override
  State<StartScreen> createState() => _StartScreen();
}

class _StartScreen extends State<StartScreen> {
  @override
  Widget build(BuildContext context) {
    final username = Provider.of<DbRepository>(context, listen: true).getUsername();

    final usernameController = TextEditingController();
    final textWidget = username != '' ?
      Text('Hello $username!') :
      TextField(
        controller: usernameController,
        decoration: const InputDecoration(
          labelText: "Username",
        ),
        textAlign: TextAlign.center,
      );

    final buttonText = username != '' ? 'Continue' : 'Set username';
    final buttonOnPressed = username != '' ?
      () async {
        Navigator.of(context)
            .push(MaterialPageRoute(builder: (context) => const MainSection()));
      } :
      () async {
        if (usernameController.text.length >= 3) {
          Provider.of<DbRepository>(context, listen: false).setUsername(usernameController.text);
        }
        else {
          Utils.showAlertDialog(context, 'The username must be longer than 3 characters!');
        }
      };

    final button = ElevatedButton(
      onPressed: buttonOnPressed,
      child: SizedBox(
        width: MediaQuery.of(context).size.width / 2,
        child: Column(
          mainAxisSize: MainAxisSize.min,
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(buttonText),
          ],
        ),
      )
    );

    return Scaffold(
      appBar: AppBar(
        title: const Text('Start screen'),
      ),
      body: Center(
        child: textWidget
      ),
      floatingActionButton: Container(
        alignment: Alignment.bottomCenter,
        child: Align(
          alignment: Alignment.bottomCenter,
          child: button,
        )
      ),
    );
  }
}
