import 'package:flutter/material.dart';
import 'package:football_team_management/domain/football_player.dart';
import 'package:football_team_management/service/football_players_service.dart';
import 'package:football_team_management/view/add_page.dart';
import 'package:provider/provider.dart';

import '../utils/pair.dart';
import 'details_page.dart';

class HomePageWidget extends StatefulWidget {
  const HomePageWidget({Key? key}) : super(key: key);

  @override
  State<HomePageWidget> createState() => _HomePageWidgetState();
}

class _HomePageWidgetState extends State<HomePageWidget> {
  Widget _buildListView() {
    var playersFuture = Provider.of<FootballPlayersService>(context, listen: true).getAllPlayers();

    return FutureBuilder<Pair>(
      future: playersFuture,
      builder: (context, snapshot) {
        var players = snapshot.data;

        return ListView.builder(
            itemCount: players?.left.length,
            itemBuilder: (context, index) {
              var player = players?.left[index];

              if (player == null) {
                return const Card();
              }

              var card = Card(
                shape: RoundedRectangleBorder(
                  side: BorderSide(
                    color: Colors.blue.shade300,
                  ),
                  borderRadius: BorderRadius.circular(15.0),
                ),
                child: ListTile(
                    title: Row(
                      children: [
                        Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: <Widget>[
                            Text(
                              player.name,
                              style: const TextStyle(
                                  color: Colors.black,
                                  fontSize: 19.0,
                                  fontWeight: FontWeight.bold),
                            ),
                            Text(
                              player.id.toString(),
                              style: const TextStyle(color: Colors.black, fontSize: 14.0),
                            )
                          ],
                        ),
                        const Spacer(),
                        Column(
                          crossAxisAlignment: CrossAxisAlignment.start,
                          children: <Widget>[
                            Text(
                              player.number.toString(),
                              style: const TextStyle(
                                  color: Colors.grey,
                                  fontSize: 19.0,
                                  fontWeight: FontWeight.bold),
                            ),
                          ],
                        ),
                      ],
                    ),

                    onTap: () => {
                      Navigator.of(context).push(
                          MaterialPageRoute<void>(
                              builder: (context) {
                                return FootballPlayerDetailsWidget(player);
                              }
                          )
                      )
                    }
                ),
              );

              if (players?.right == false && index == 0) {
                return Container(
                  padding:
                  const EdgeInsets.symmetric(vertical: 5.0, horizontal: 10.0),
                  child: Column(children: [const Text("Offline"), card]),
                );
              }

              return card;
            }
        );
      }
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.of(context).push(
              MaterialPageRoute<void>(
                  builder: (context) {
                    return const FootballPlayerAddPage();
                  }
              )
          );
        },
        backgroundColor: Colors.blue,
        child: const Icon(Icons.add),
      ),
      body: _buildListView(),
    );
  }
}
