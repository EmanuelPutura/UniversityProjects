import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_25a/view/category_items_list_widget.dart';
import '../repository/db_repository.dart';
import 'add_item_section.dart';

class CategoryItemsSection extends StatefulWidget {
  final String _category;

  const CategoryItemsSection(this._category, {Key? key}) : super(key: key);

  @override
  State<CategoryItemsSection> createState() => _CategoryItemsSection();
}

class _CategoryItemsSection extends State<CategoryItemsSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text("Category '${widget._category}' Items"),
        ),
        body: CategoryItemsListWidget(widget._category),
        floatingActionButton: Container(
          alignment: Alignment.bottomCenter,
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Spacer(),
              ElevatedButton(
                onPressed: () {
                  Navigator.of(context)
                      .push(MaterialPageRoute(builder: (context) => AddItemSection(widget._category)));
                },
                child: const Text('Add Item'),
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
