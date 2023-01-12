import 'package:animal_shelter/animal_service.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import 'animal.dart';
import 'main.dart';

class UpdateRemoveScreen extends StatefulWidget {
  UpdateRemoveScreen(this._animal, {super.key}) {
    name_controller = TextEditingController(text: _animal.name);
    age_controller = TextEditingController(text: _animal.age.toString());
    breed_controller = TextEditingController(text: _animal.breed);
    description_controller = TextEditingController(text: _animal.description);
  }

  final Animal _animal;
  TextEditingController name_controller = TextEditingController();
  TextEditingController age_controller = TextEditingController();
  TextEditingController breed_controller = TextEditingController();
  TextEditingController description_controller = TextEditingController();

  @override
  _UpdateRemoveState createState() => _UpdateRemoveState();
}

class _UpdateRemoveState extends State<UpdateRemoveScreen> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Update/Remove Animal"),
      ),
      body: Column(
        children: [
          TextFormField(
            controller: widget.name_controller,
            decoration: const InputDecoration(
                labelText: "Name:"
            ),
          ),
          TextFormField(
            controller: widget.age_controller,
            decoration: const InputDecoration(
                labelText: "Age:"
            ),
            keyboardType: TextInputType.number,
          ),
          TextFormField(
            controller: widget.breed_controller,
            decoration: const InputDecoration(
                labelText: "Breed:"
            ),
          ),
          TextFormField(
            controller: widget.description_controller,
            decoration: const InputDecoration(
                labelText: "Description:"
            ),
          ),
        ],
      ),
      floatingActionButton: Row(
          mainAxisAlignment: MainAxisAlignment.spaceAround,
          children: [
            FloatingActionButton(
              heroTag: "sellButton",
              onPressed: () {
                showDialog (
                  context: context,
                  builder: (BuildContext context) {
                  return AlertDialog(
                    title: const Text("Sell"),
                    content: const Text("Are you sure you want to proceed?"),

                  actions: [
                    ElevatedButton(
                        onPressed: () {
                          var res = Provider.of<AnimalService>(context, listen: false)
                            .remove(
                              widget._animal.id
                          );
                          res.then((value) => {
                            if (value == "SUCCESS") {
                              Navigator.of(context).push(MaterialPageRoute(builder: (context)=>HomeScreen()))
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
                                        Navigator.of(context).push(MaterialPageRoute(builder: (context)=>HomeScreen()));
                                      },
                                        child: const Text("OK")
                                      )
                                      ],
                                      );
                                  }
                              )
                              }
                            });
                            },
                        child: const Text("Yes")
                    ),
                    ElevatedButton(
                        onPressed: () {
                          Navigator.pop(context);
                          },
                        child: const Text("No")
                    ),
                  ],
                );},); },
              child: const Text("Sell"),
            ),
            FloatingActionButton(
              heroTag: "updateButton",
              onPressed: () {
                var res = Provider.of<AnimalService>(context, listen: false)
                  .update(
                    widget._animal.id,
                    widget.name_controller.text,
                    int.parse(widget.age_controller.text),
                    widget.breed_controller.text,
                    widget.description_controller.text
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
                                    Navigator.pop(context);
                                    Navigator.pop(context);
                                  },
                                  child: const Text("OK")
                              )
                            ],
                          );
                        }
                    )
                  }
                });
                },
              child: const Text("Update"),
            )],
    ));
  }
}