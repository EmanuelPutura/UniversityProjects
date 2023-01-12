import 'package:animal_shelter/animal.dart';
import 'package:animal_shelter/update_remove_screen.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class AnimalItem extends StatelessWidget{
    const AnimalItem(this.animal, {Key? key}) : super(key: key);

    final Animal animal;

    @override
    Widget build(BuildContext context) {
      return InkWell(child: Container(
            height: 80.0,
            decoration: BoxDecoration(
                color: Colors.blue[50],
                border: Border.all(color: Colors.blue, width: 2),
                borderRadius: BorderRadius.circular(20.0),
            ),
            margin: const EdgeInsets.symmetric(vertical: 3.0, horizontal: 2.5),
            padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 10.0),
              child: Row(
                  children: [
                  Flexible(child: Image.asset('images/Cartoon-Black-Dog-177605538.png')),
                  Container(
                    padding: const EdgeInsets.symmetric(horizontal: 16.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                          Text(animal.name),
                          Text(animal.age.toString()),
                          Text(animal.breed)
                      ],
                    ),
                  )],),),
          onTap: () {
            Navigator.of(context).push(MaterialPageRoute(builder: (context)=>UpdateRemoveScreen(animal)));
          },
      );
    }
}