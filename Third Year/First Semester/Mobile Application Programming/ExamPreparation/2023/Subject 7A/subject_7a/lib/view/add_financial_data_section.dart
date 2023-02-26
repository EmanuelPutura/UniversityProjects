import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../persistence/db_repository.dart';
import '../utils/http_out_message.dart';
import '../utils/utils.dart';

class AddFinancialDataSection extends StatefulWidget {
  const AddFinancialDataSection({Key? key}) : super(key: key);

  @override
  State<AddFinancialDataSection> createState() => _AddFinancialDataSection();
}

class _AddFinancialDataSection extends State<AddFinancialDataSection> {
  bool isLoading = false;

  @override
  Widget build(BuildContext context) {
    var dateController = TextEditingController();
    var typeController = TextEditingController();
    var amountController = TextEditingController();
    var categoryController = TextEditingController();
    var descriptionController = TextEditingController();

    return Scaffold(
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Add financial data'),
        ),
        body: SingleChildScrollView(
          child: Column(
            children: [
              ListTile(
                  leading: const Icon(Icons.person),
                  title: TextField(
                      controller: dateController,
                      decoration: const InputDecoration(
                        labelText: "Date",
                      ))),
              ListTile(
                  leading: const Icon(Icons.add_location_alt_outlined),
                  title: TextField(
                      controller: typeController,
                      decoration: const InputDecoration(
                        labelText: "Type",
                      ))),
              ListTile(
                  leading: const Icon(Icons.dehaze_outlined),
                  title: TextField(
                      controller: amountController,
                      decoration: const InputDecoration(
                        labelText: "Amount",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
                      controller: categoryController,
                      decoration: const InputDecoration(
                        labelText: "Category",
                      ))),
              ListTile(
                  leading: const Icon(Icons.line_weight),
                  title: TextField(
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
                        Text("Add financial data"),
                      ],
                    ),
                  ),
                  onPressed: () async {
                    setState(() {
                      isLoading = true;
                    });

                    final amountNum = num.tryParse(amountController.text);

                    if (amountNum == null) {
                      Utils.showAlertDialog(context, 'The provided entity details are invalid!');
                      isLoading = false;
                      return;
                    }

                    var httpOutMessage = await Provider.of<DbRepository>(context, listen: false).addFinancialData(
                        dateController.text,
                        typeController.text,
                        amountNum,
                        categoryController.text,
                        descriptionController.text
                    );

                    setState(() {
                      isLoading = false;
                    });

                    final serverResponse = httpOutMessage.serverResponse;
                    final online = httpOutMessage.online;

                    if (!mounted) {
                      return;
                    }

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
                      Utils.showAlertDialog(context, "Add is not possible while offline!");
                    }
                  },
                ) : const Center(child:CircularProgressIndicator()),
              ),
            ],
          ),
        )
    );
  }
}
