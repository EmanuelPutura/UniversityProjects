import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_2b/persistence/db_repository.dart';
import 'package:subject_2b/view/main_section.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  var service = await DbRepository.init();

  runApp(
      ChangeNotifierProvider(
          create: (_) => service,
          child: const MaterialApp(
              title: 'Main section',
              home: MainSection()
          )
      )
  );
}
