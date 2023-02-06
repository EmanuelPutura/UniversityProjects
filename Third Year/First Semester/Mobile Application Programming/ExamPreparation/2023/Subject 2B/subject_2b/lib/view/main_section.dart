import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_2b/view/add_activity_section.dart';
import 'package:subject_2b/view/intensity_section.dart';

import '../persistence/db_repository.dart';
import 'list_widgets/categories_list_widget.dart';

class MainSection extends StatefulWidget {
  const MainSection({Key? key}) : super(key: key);

  @override
  State<MainSection> createState() => _MainSection();
}

class _MainSection extends State<MainSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Main Section'),
        ),
        body: const CategoriesListWidget(),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (context) => const IntensitySection()));
                },
                child: const Text('Intensity Section'),
              ),
              ElevatedButton(
                onPressed: () {
                  Provider.of<DbRepository>(context, listen: false).checkOnline();
                },
                child: const Text("Refresh"),
              ),
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (context) => const AddActivitySection()));
                },
                child: const Text("Add activity"),
              ),
            ],
          ),
        )
    );
  }
}
