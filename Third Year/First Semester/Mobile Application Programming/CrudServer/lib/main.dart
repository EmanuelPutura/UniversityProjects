import 'package:animal_shelter/add_screen.dart';
import 'package:animal_shelter/animal_item.dart';
import 'package:animal_shelter/animal_service.dart';
import 'package:animal_shelter/pair.dart';
import 'package:flutter/material.dart';
import 'package:animal_shelter/animal.dart';
import 'package:provider/provider.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  var service = await AnimalService.init();

  runApp(ChangeNotifierProvider(create: (_) => service, child: const MyApp()));
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Pet shop',
      home: HomeScreen(),
    );
  }
}

class HomeScreen extends StatefulWidget {
  @override
  _HomeState createState() => _HomeState();
}

class _HomeState extends State<HomeScreen> {
  Widget _buildBodyView(BuildContext context) {
    var animalsFuture =
        Provider.of<AnimalService>(context, listen: true).getAll();

    return FutureBuilder<Pair>(
      future: animalsFuture,
      builder: (context, snapshot) {
        var animals = snapshot.data;

        return ListView.builder(
          itemBuilder: (BuildContext context, int index) {
            var animal = animals?.left[index];
            if (animals?.right == false && index == 0) {
              return Container(
                padding:
                    const EdgeInsets.symmetric(vertical: 5.0, horizontal: 10.0),
                child: Column(children: [const Text("Offline"), AnimalItem(animal)]),
              );
            }

            if (animal == null) {
              return const Card();
            }

            return AnimalItem(animal);
          },
          itemCount: animals?.left.length,
        );
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Pet shop'),
      ),
      body: _buildBodyView(context),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.of(context)
              .push(MaterialPageRoute(builder: (context) => AddScreen()));
        },
        child: const Icon(Icons.add),
      ),
    );
  }
}
