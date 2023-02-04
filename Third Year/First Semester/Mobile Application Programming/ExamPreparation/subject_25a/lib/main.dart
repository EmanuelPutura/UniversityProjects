import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:subject_25a/service/main_service.dart';
import 'package:subject_25a/view/main_section.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  var service = await MainService.init();

  runApp(
    ChangeNotifierProvider(
      create: (_) => service,
      child: const MaterialApp(
        title: 'Main Section',
        home: MainSection()
      )
    )
  );
}
