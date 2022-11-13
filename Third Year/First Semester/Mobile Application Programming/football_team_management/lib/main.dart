import 'package:flutter/material.dart';
import 'package:football_team_management/service/football_players_service.dart';
import 'package:football_team_management/view/home_page.dart';
import 'package:provider/provider.dart';

void main() {
  runApp(
      ChangeNotifierProvider(
          create: (_) => FootballPlayersService(),
          child: MaterialApp(
            title: 'Football Team Management Application',
            home: Scaffold(
              appBar: AppBar(
                title: const Text('Football Team Management Application'),
              ),
            body: const HomePageWidget(),
            )
          )
      ),
  );
}
