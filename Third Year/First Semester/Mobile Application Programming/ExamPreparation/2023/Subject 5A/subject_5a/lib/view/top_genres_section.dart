import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_5a/view/top_genres_list_widget.dart';

import '../repository/db_repository.dart';
import 'main_section.dart';

class TopGenresSection extends StatefulWidget {
  const TopGenresSection({Key? key}) : super(key: key);

  @override
  State<TopGenresSection> createState() => _TopGenresSection();
}

class _TopGenresSection extends State<TopGenresSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Top genres section'),
        ),
        body: const TopGenresListWidget(),
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
            ],
          ),
        )
    );
  }
}
