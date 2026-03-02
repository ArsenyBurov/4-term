from typing import Type


from sqlalchemy.orm import Session
from infrastructure.sqlite.models.users import User
#from infrastructure.sqlite.database


class UserRepository:
    def __init__(self):
        user=User
        self._model: Type[User] = User

    def get(self, session: Session) -> User:
        query = {
            session.query(User, login: str)
            .where(User.login == "user_555")
        }

        return query.scalar()