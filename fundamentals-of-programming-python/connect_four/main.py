from domain.entities import Board
from services.service import Service
from ui.console import Console


if __name__ == '__main__':
    board = Board(7, 7)
    service = Service(board)
    console = Console(service)
    console.run_main()
