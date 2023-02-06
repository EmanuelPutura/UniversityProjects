import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_7a/repository/db_repository.dart';
import 'package:subject_7a/view/start_screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  var service = await DbRepository.init();

  runApp(
      ChangeNotifierProvider(
          create: (_) => service,
          child: const MaterialApp(
              title: 'Main Section',
              home: StartScreen()
          )
      )
  );
}
