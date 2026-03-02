from infrastructure.sqlite.database import database
from infrastructure.sqlite.repositories.users import UserRepository
from infrastructure.sqlite

class GetUsersByLoginUseCase:
    def __init__(self):
        self.database = database
