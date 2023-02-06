import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_2b/view/list_widgets/category_activities_list_widget.dart';

import '../persistence/db_repository.dart';

class CategoryActivitiesSection extends StatefulWidget {
  final String _category;

  const CategoryActivitiesSection(this._category, {Key? key}) : super(key: key);

  @override
  State<CategoryActivitiesSection> createState() => _CategoryActivitiesSection();
}

class _CategoryActivitiesSection extends State<CategoryActivitiesSection> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          title: Text("Category '${widget._category}' activities"),
        ),
        body: CategoryActivitiesListWidget(widget._category),
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
