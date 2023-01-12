import logging
import sqlite3

from sqlite3 import Error, Connection

from player import Player

logger = logging.getLogger('debugLogger')
logger.setLevel(logging.DEBUG)


def sql_connection() -> Connection:
    try:
        conn = sqlite3.connect("football_team.db")
        create_players_table(conn)

        return conn
    except Error:
        print("Failed to connect to database")
        exit(1)


def create_players_table(conn: Connection):
    curs = conn.cursor()

    curs.execute("""
        CREATE TABLE IF NOT EXISTS Players(
            id INTEGER PRIMARY KEY AUTOINCREMENT, 
            name TEXT, 
            position TEXT,
            number INTEGER, 
            height INTEGER,
            weight REAL);
    """)

    conn.commit()


def get_players_db(conn: Connection) -> [Player]:
    curs = conn.cursor()

    rows = curs.execute("""
        SELECT* FROM Players;
    """).fetchall()

    players = []
    for row in rows:
        player = Player(int(row[0]), row[1], row[2], int(row[3]), int(row[4]), float(row[5]))
        players.append(player)

        logger.debug(
            f"get_player_db - Player: {player.id}, {player.name}, {player.position}, {player.number}, {player.height}, {player.weight}")

    return players


def get_player_db(conn: Connection, id: int) -> Player | None:
    curs = conn.cursor()

    rows = curs.execute(f"""
        SELECT* FROM Players WHERE id={id};
    """).fetchall()

    if len(rows) != 1:
        logger.debug(f"More instances with the same id")

        return None

    else:
        player = Player(int(rows[0][0]), rows[0][1], rows[0][2], int(rows[0][3]), int(rows[0][4]), float(rows[0][5]))
        logger.debug(
            f"get_player_db - Player: {player.id}, {player.name}, {player.position}, {player.number}, {player.height}, {player.weight}")

        return player


def add_player_db(conn: Connection, player: Player):
    curs = conn.cursor()

    curs.execute(f"""
        INSERT INTO Players(name, position, number, height, weight) VALUES(
            '{player.name}',
            '{player.position}',
            {player.number},
            {player.height},
            {player.weight}
        );
    """)

    logger.debug(f"add_player_db - Player: {player.id}, {player.name}, {player.position}, {player.number}, {player.height}, {player.weight}")

    conn.commit()


def update_player_db(conn: Connection, other: Player):
    curs = conn.cursor()

    curs.execute(f"""
        UPDATE Players 
        SET 
        name = '{other.name}',
        position = '{other.position}',
        number = {other.number},
        height = {other.height},
        weight = {other.weight}
        WHERE id = {other.id};
    """)

    logger.debug(
        f"update_player_db - Player: {other.id}, {other.name}, {other.position},"
        f" {other.number}, {other.height}, {other.weight}")

    conn.commit()


def delete_player_db(conn: Connection, player_id: int):
    curs = conn.cursor()

    curs.execute(f"""
        DELETE FROM Players WHERE id={player_id};
    """)

    logger.debug(f"delete_player_db - Player: {player_id}")

    conn.commit()
