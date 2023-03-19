from src.repository.client_repo import ClientRepo
from src.repository.movie_repo import MovieRepo
from src.repository.rental_repo import RentalRepo
from src.services.client_service import ClientService
from src.services.movie_service import MovieService
from src.services.rental_service import RentalService
from src.ui.console import Console

movie_repo = MovieRepo()

client_repo = ClientRepo()

rental_repo = RentalRepo()
rental_service = RentalService(rental_repo, client_repo, movie_repo)

client_service = ClientService(client_repo, rental_service)
movie_service = MovieService(movie_repo, rental_service)

client_service.generate_random()
movie_service.generate_random()
rental_service.generate_random()

console = Console(movie_service, client_service, rental_service)

if __name__ == '__main__':
    console.main_menu()
