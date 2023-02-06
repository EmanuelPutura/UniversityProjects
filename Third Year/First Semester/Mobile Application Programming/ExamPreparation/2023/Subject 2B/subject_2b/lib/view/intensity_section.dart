import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_2b/view/add_activity_section.dart';
import 'package:subject_2b/view/list_widgets/easiest_activities_list_widget.dart';

import '../persistence/db_repository.dart';
import 'list_widgets/categories_list_widget.dart';

class IntensitySection extends StatefulWidget {
  const IntensitySection({Key? key}) : super(key: key);

  @override
  State<IntensitySection> createState() => _IntensitySection();
}

class _IntensitySection extends State<IntensitySection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Intensity Section'),
        ),
        body: const EasiestActivitiesListWidget(),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context).pop();
                },
                child: const Text('Main Section'),
              ),
              ElevatedButton(
                onPressed: () {
                  Provider.of<DbRepository>(context, listen: false).checkOnline();
                },
                child: const Text("Refresh"),
              ),
            ],
          ),
        )
    );
  }
}
