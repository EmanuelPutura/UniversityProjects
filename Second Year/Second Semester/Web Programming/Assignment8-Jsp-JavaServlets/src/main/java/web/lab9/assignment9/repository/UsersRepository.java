package web.lab9.assignment9.repository;

import web.lab9.assignment9.model.User;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;

public class UsersRepository extends GenericRepository<String, User> {
    public UsersRepository() {
        super("users", "username");
    }

    @Override
    protected Optional<User> getEntityFromResultSet(ResultSet resultSet) {
        try {
            if (resultSet.next()){
                String username = resultSet.getString("username");
                String password = resultSet.getString("password");

                return Optional.of(new User(username, password));
            }
        } catch (SQLException e) {
            return Optional.empty();
        }
        return Optional.empty();
    }
}
