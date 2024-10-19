from src.domain.board import Board
from src.service.service import Service
from src.ui.console import Console

if __name__ == '__main__':
    board = Board()
    service = Service(board)
    console = Console(service)
    console.run()
