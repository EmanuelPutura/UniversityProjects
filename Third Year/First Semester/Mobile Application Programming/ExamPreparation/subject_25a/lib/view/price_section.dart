import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_25a/view/discounted_items_list_widget.dart';
import 'package:subject_25a/view/main_section.dart';

import '../repository/db_repository.dart';

class PriceSection extends StatefulWidget {
  const PriceSection({Key? key}) : super(key: key);

  @override
  State<PriceSection> createState() => _PriceSection();
}

class _PriceSection extends State<PriceSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: const Text('Price Section'),
        ),
        body: const DiscountedItemsListWidget(),
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
                child: const Text('Main Section'),
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
