import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_5a/view/active_years_list_widget.dart';
import 'package:subject_5a/view/top_genres_section.dart';

import '../repository/db_repository.dart';
import 'main_section.dart';

class ReleaseYearSection extends StatefulWidget {
  const ReleaseYearSection({Key? key}) : super(key: key);

  @override
  State<ReleaseYearSection> createState() => _ReleaseYearSection();
}

class _ReleaseYearSection extends State<ReleaseYearSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Release year section'),
        ),
        body: const ActiveYearsListWidget(),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Spacer(),
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (context) => const MainSection()));
                },
                child: const Text('Main section'),
              ),
              const Spacer(),
              ElevatedButton(
                onPressed: () {
                  Provider.of<DbRepository>(context, listen: false).checkOnline();
                },
                child: const Text("Refresh"),
              ),
              const Spacer(),
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (context) => const TopGenresSection()));
                },
                child: const Text("Top 3 genres"),
              ),
              const Spacer(),
            ],
          ),
        )
    );
  }
}
