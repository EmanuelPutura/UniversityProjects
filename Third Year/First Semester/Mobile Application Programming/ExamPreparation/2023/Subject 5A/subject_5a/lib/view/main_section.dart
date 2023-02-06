import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_5a/view/add_movie_section.dart';
import 'package:subject_5a/view/genres_list_widget.dart';
import 'package:subject_5a/view/release_year_section.dart';
import '../repository/db_repository.dart';

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
        body: const GenresListWidget(),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Spacer(),
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (context) => const ReleaseYearSection()));
                },
                child: const Text('Release year section'),
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
                      .push(MaterialPageRoute(builder: (context) => const AddMovieSection()));
                },
                child: const Text("Add movie"),
              ),
              const Spacer(),
            ],
          ),
        )
    );
  }
}
