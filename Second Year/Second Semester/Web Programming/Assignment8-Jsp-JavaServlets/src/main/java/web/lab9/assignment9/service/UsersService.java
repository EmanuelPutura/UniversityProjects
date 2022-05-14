package web.lab9.assignment9.service;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.model.User;
import web.lab9.assignment9.repository.Repository;

public class UsersService extends GenericService<String, User> {
    public UsersService(Repository<String, User> repository) {
        super(repository);
    }

    public boolean checkPassword(String username, String password) {
        try {
            var userOptional = repository.findOneByPrimaryKey(username);
            if (userOptional.isEmpty()) {
                return false;
            }

            return userOptional.get().checkPassword(password);
        } catch (AppException e) {
            return false;
        }
    }
}
