import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../domain/movie.dart';
import '../repository/db_repository.dart';

class DeleteMovieSection extends StatefulWidget {
  final Movie _movie;

  const DeleteMovieSection(this._movie, {Key? key}) : super(key: key);

  @override
  State<DeleteMovieSection> createState() => _DeleteMovieSection();
}

class _DeleteMovieSection extends State<DeleteMovieSection> {
  bool isDeleteLoading = false;

  void showAreYouSureDialog() {
    // set up the button
    Widget yesButton = TextButton(
        child: const Text("Yes"),
        onPressed: () async {
          setState(() {
            isDeleteLoading = true;
          });

          var result = await Provider.of<DbRepository>(context, listen: false).deleteMovie(
              widget._movie.id
          );

          setState(() {
            isDeleteLoading = false;
          });

          if (result.left is String && result.left != "ok") {
            final snackBar = SnackBar(
              content: Text(result.left as String),
            );

            ScaffoldMessenger.of(context).showSnackBar(snackBar);
            return;
          }

          if (result.right is bool && result.right) {
            Navigator.pop(context);
          }
          else {
            showAlertDialog(context, "Delete is not possible while offline!");
          }
        }
    );

    Widget cancelButton = TextButton(
      child: const Text("Cancel"),
      onPressed: () {
        Navigator.pop(context);
      },
    );

    // set up the AlertDialog
    AlertDialog alert = AlertDialog(
      title: const Text("Error"),
      content: const Text('Are you sure you want to remove this entity?'),
      actions: [
        cancelButton,
        yesButton,
      ],
    );

    // show the dialog
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return alert;
      },
    );
  }

  void showAlertDialog(BuildContext context, String message) {
    // set up the button
    Widget okButton = TextButton(
      child: const Text("OK"),
      onPressed: () {
        Navigator.pop(context);
      },
    );

    // set up the AlertDialog
    AlertDialog alert = AlertDialog(
      title: const Text("Error"),
      content: Text(message),
      actions: [
        okButton,
      ],
    );

    // show the dialog
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return alert;
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    // final storage = Provider.of<DbRepository>(context);
    // final infoMessage = storage.getInfoMessage();
    //
    // if (infoMessage != '') {
    //   return AlertDialog(
    //     title: const Text('Alert'),
    //     content: SingleChildScrollView(
    //       child: ListBody(
    //         children: <Widget>[
    //           Text(infoMessage)
    //         ],
    //       ),
    //     ),
    //     actions: [
    //       TextButton(
    //         child: const Text("OK"),
    //         onPressed: () {
    //           storage.setInfoMessage('');
    //         },
    //       )
    //     ],
    //   );
    // }

    var nameController = TextEditingController();
    nameController.text = widget._movie.name;

    var descriptionController = TextEditingController();
    descriptionController.text = widget._movie.description;

    var genreController = TextEditingController();
    genreController.text = widget._movie.genre;

    var directorController = TextEditingController();
    directorController.text = widget._movie.director;

    var yearController = TextEditingController();
    yearController.text = widget._movie.year.toString();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Delete movie'),
        ),
        body: SingleChildScrollView(
          child: Column(
            children: [
              ListTile(
                  leading: const Icon(Icons.person),
                  title: TextField(
                      readOnly: true,
                      controller: nameController,
                      decoration: const InputDecoration(
                        labelText: "Name",
                      ))),
              ListTile(
                  leading: const Icon(Icons.add_location_alt_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: descriptionController,
                      decoration: const InputDecoration(
                        labelText: "Description",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: genreController,
                      decoration: const InputDecoration(
                        labelText: "Genre",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: directorController,
                      decoration: const InputDecoration(
                        labelText: "Director",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: yearController,
                      decoration: const InputDecoration(
                        labelText: "Year",
                      ))),
              Center(
                child: !isDeleteLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Delete movie"),
                      ],
                    ),
                  ),
                  onPressed: () {
                    showAreYouSureDialog();
                  },
                ) : const Center(child:CircularProgressIndicator()),
              ),
            ],
          ),
        )
    );
  }
}
