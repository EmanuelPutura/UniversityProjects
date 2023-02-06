import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_5a/view/genre_movies_list_widget.dart';
import '../repository/db_repository.dart';

class GenreMoviesSection extends StatefulWidget {
  final String _genre;

  const GenreMoviesSection(this._genre, {Key? key}) : super(key: key);

  @override
  State<GenreMoviesSection> createState() => _GenreMoviesSection();
}

class _GenreMoviesSection extends State<GenreMoviesSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text("Genre '${widget._genre}' movies"),
        ),
        body: GenreMoviesListWidget(widget._genre),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
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
