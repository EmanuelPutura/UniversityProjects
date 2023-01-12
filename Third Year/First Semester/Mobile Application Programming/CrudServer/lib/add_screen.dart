import 'package:animal_shelter/animal_service.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class AddScreen extends StatefulWidget {
    @override
    _AddState createState() => _AddState();
}

class _AddState extends State<AddScreen> {
    TextEditingController name_controller = TextEditingController();
    TextEditingController age_controller = TextEditingController();
    TextEditingController breed_controller = TextEditingController();
    TextEditingController description_controller = TextEditingController();

    @override
    Widget build(BuildContext context) {
        return Scaffold(
          appBar: AppBar(
              title: const Text("Add Animal"),
          ),
          body: Column(
            children: [
              TextFormField(
                controller: name_controller,
                decoration: const InputDecoration(
                  labelText: "Name:"
                ),
              ),
              TextFormField(
                controller: age_controller,
                decoration: const InputDecoration(
                    labelText: "Age:"
                ),
                keyboardType: TextInputType.number,
              ),
              TextFormField(
                controller: breed_controller,
                decoration: const InputDecoration(
                    labelText: "Breed:"
                ),
              ),
              TextFormField(
                controller: description_controller,
                decoration: const InputDecoration(
                    labelText: "Description:"
                ),
              ),
            ],
          ),
          floatingActionButton: FloatingActionButton(
            onPressed: () {
              Provider.of<AnimalService>(context, listen: false)
                .add(
                name_controller.text,
                int.parse(age_controller.text),
                breed_controller.text,
                description_controller.text
              );

              Navigator.pop(context);
              },
            child: const Text("Add"),
          ),
        );
    }
}