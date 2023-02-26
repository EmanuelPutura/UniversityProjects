import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_7a/domain/financial_data.dart';

import '../persistence/db_repository.dart';
import '../utils/http_out_message.dart';
import '../utils/utils.dart';

class DeleteFinancialDataSection extends StatefulWidget {
  final FinancialData _financialData;

  const DeleteFinancialDataSection(this._financialData, {Key? key}) : super(key: key);

  @override
  State<DeleteFinancialDataSection> createState() => _DeleteFinancialDataSection();
}

class _DeleteFinancialDataSection extends State<DeleteFinancialDataSection> {
  bool isLoading = false;

  void showAreYouSureDialog() {
    // set up the button
    Widget yesButton = TextButton(
        child: const Text("Yes"),
        onPressed: () async {
          setState(() {
            isLoading = true;
          });

          var httpOutMessage = await Provider.of<DbRepository>(context, listen: false).deleteFinancialData(
              widget._financialData.id
          );

          setState(() {
            isLoading = false;
          });

          if (!mounted) {
            return;
          }

          final serverResponse = httpOutMessage.serverResponse;
          final online = httpOutMessage.online;

          if (serverResponse != HttpOutMessage.okServerMessage) {
            final snackBar = SnackBar(
              content: Text(serverResponse),
            );

            ScaffoldMessenger.of(context).showSnackBar(snackBar);
            return;
          }

          if (online) {
            Navigator.pop(context);
          }
          else {
            Utils.showAlertDialog(context, "Delete is not possible while offline!");
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

  @override
  Widget build(BuildContext context) {
    final storage = Provider.of<DbRepository>(context);
    final infoMessage = storage.getInfoMessage();

    if (infoMessage != '') {
      return AlertDialog(
        title: const Text('Alert'),
        content: SingleChildScrollView(
          child: ListBody(
            children: <Widget>[
              Text(infoMessage)
            ],
          ),
        ),
        actions: [
          TextButton(
            child: const Text("OK"),
            onPressed: () {
              storage.setInfoMessage('');
            },
          )
        ],
      );
    }

    var dateController = TextEditingController();
    dateController.text = widget._financialData.date;

    var typeController = TextEditingController();
    typeController.text = widget._financialData.type;

    var amountController = TextEditingController();
    amountController.text = widget._financialData.amount.toString();

    var categoryController = TextEditingController();
    categoryController.text = widget._financialData.category;

    var descriptionController = TextEditingController();
    descriptionController.text = widget._financialData.description;

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Delete financial data'),
        ),
        body: SingleChildScrollView(
          child: Column(
            children: [
              ListTile(
                  leading: const Icon(Icons.person),
                  title: TextField(
                      readOnly: true,
                      controller: dateController,
                      decoration: const InputDecoration(
                        labelText: "Date",
                      ))),
              ListTile(
                  leading: const Icon(Icons.add_location_alt_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: typeController,
                      decoration: const InputDecoration(
                        labelText: "Type",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      readOnly: true,
                      controller: amountController,
                      decoration: const InputDecoration(
                        labelText: "Amount",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: categoryController,
                      decoration: const InputDecoration(
                        labelText: "Category",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      readOnly: true,
                      controller: descriptionController,
                      decoration: const InputDecoration(
                        labelText: "Description",
                      ))),
              Center(
                child: !isLoading ? ElevatedButton(
                  child: SizedBox(
                    width: MediaQuery.of(context).size.width / 2,
                    child: Column(
                      mainAxisSize: MainAxisSize.min,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: const [
                        Text("Delete financial data"),
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
