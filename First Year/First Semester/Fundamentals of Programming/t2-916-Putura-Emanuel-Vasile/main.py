from infrastructure.memo_repository import Repository
from infrastructure.text_repository import TextRepository
from presentation.consoleUI import ConsoleUI
from services.player_service import PlayerService
from services.torunament_service import TournamentService
from validators.player_validator import PlayerValidator

if __name__ == "__main__":
    player_repository = TextRepository("data/players.txt")
    tournament_repository = Repository()
    player_service = PlayerService(player_repository, PlayerValidator())
    tournament_service = TournamentService(player_repository, tournament_repository)
    console = ConsoleUI(player_service, tournament_service)
    console.run()
