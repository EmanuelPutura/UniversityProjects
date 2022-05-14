package web.lab9.assignment9.repository.users;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.model.User;
import web.lab9.assignment9.repository.Repository;

public interface UsersRepositoryFactory {
    static Repository<String, User> getInstance(String realFilePath) {
        try {
            return new UsersRepository(realFilePath);
        } catch (AppException e) {
            return null;
        }
    }
}
