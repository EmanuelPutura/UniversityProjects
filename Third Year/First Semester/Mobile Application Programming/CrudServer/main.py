import asyncio
import json
from threading import Thread

import websockets
from flask import Flask, request

from dbutils import *

app = Flask(__name__)


CLIENTS = []


@app.route("/", methods=['GET'])
def check():
    return "SUCCESS"


@app.route("/player", methods=['GET'])
def get_players():
    conn = sql_connection()
    players = get_players_db(conn)
    conn.close()

    players_json = [player.as_dict() for player in players]

    return json.dumps({'players': players_json})


@app.route("/player/sync", methods=['POST'])
def players_sync():
    conn = sql_connection()
    players = get_players_db(conn)

    players_json = json.loads(request.data)
    players_to_add = []

    for player_json in json.loads(players_json['players']):
        found = False
        for player in players:
            if player_json['name'] == player.name \
                    and player_json['position'] == player.position \
                    and player_json['number'] == player.number \
                    and player_json['height'] == player.height \
                    and player_json['weight'] == player.weight:
                found = True
        if not found:
            players_to_add.append(
                Player(0, player_json['name'], player_json['position'], player_json['number'], player_json['height'], player_json['weight']))

    for player in players_to_add:
        add_player_db(conn, player)
    players = get_players_db(conn)
    conn.close()

    players_json = [player.as_dict() for player in players]

    return json.dumps({'players': players_json})


@app.route("/player/<id>", methods=['GET'])
def get_player(id):
    conn = sql_connection()
    player = get_player_db(conn, id)
    conn.close()

    if player is None:
        return "ERROR"

    return json.dumps(player.as_dict())


@app.route("/player", methods=['POST'])
def add_player():
    player_json = json.loads(request.data)
    conn = sql_connection()
    add_player_db(conn, Player(0, player_json['name'], player_json['position'], player_json['number'], player_json['height'], player_json['weight']))
    conn.close()

    asyncio.run(broadcast("ADD$" + str(request.data, "UTF-8")))

    return "SUCCESS"


@app.route("/player", methods=['PUT'])
def update_player():
    player_json = json.loads(request.data)
    conn = sql_connection()
    update_player_db(conn,
                     Player(player_json['id'], player_json['name'], player_json['position'], player_json['number'],
                            player_json['height'], player_json['weight']))
    conn.close()

    asyncio.run(broadcast("UPDATE$" + str(request.data, "UTF-8")))

    return "SUCCESS"


@app.route("/player/<id>", methods=['DELETE'])
def delete_player(id):
    conn = sql_connection()
    delete_player_db(conn, id)
    conn.close()

    asyncio.run(broadcast("DELETE$" + id))

    return "SUCCESS"


async def send(websocket, message):
    try:
        await websocket.send(message)
    except websockets.ConnectionClosed:
        CLIENTS.remove(websocket)
        pass


async def broadcast(message):
    for websocket in CLIENTS:
        asyncio.create_task(send(websocket, message))


async def echo(websocket):
    CLIENTS.append(websocket)
    try:
        # data = await websocket.recv()
        # print(data)

        await websocket.wait_closed()
    finally:
        CLIENTS.remove(websocket)


async def main_sockets():
    async with websockets.serve(echo, "192.168.43.241", 8765, ssl=None):
        await asyncio.Future()


def routine1():
    asyncio.run(main_sockets(), debug=False)


def routine2():
    app.run(host="192.168.43.241", debug=False, threaded=True)


if __name__ == "__main__":
    thread_web = Thread(target=routine1)
    thread_server = Thread(target=routine2)
    thread_server.start()
    thread_web.start()
