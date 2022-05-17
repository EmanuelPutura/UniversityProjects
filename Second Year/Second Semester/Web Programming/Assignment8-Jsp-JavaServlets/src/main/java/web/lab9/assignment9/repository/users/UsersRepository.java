package web.lab9.assignment9.repository.users;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.model.User;
import web.lab9.assignment9.repository.GenericRepository;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;
import java.util.stream.Stream;

public class UsersRepository extends GenericRepository<String, User> {
    public UsersRepository(String configFilePath) throws AppException {
        super(configFilePath, "users", "username");
    }

    @Override
    public void save(User entity) throws AppException {
        if (entity == null) {
            throw new AppException("Entity must not be null!");
        }

        String insertSqlQuery = "INSERT INTO users(username, password) VALUES(?, ?) ON CONFLICT(username) DO UPDATE " +
                "SET username = excluded.username, password = excluded.password";
        try(var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
            var statement = connection.prepareStatement(insertSqlQuery);
        ) {
            statement.setString(1, entity.getUsername());
            statement.setString(2, entity.getPassword());

            statement.executeUpdate();
        } catch (SQLException e) {
            throw new AppException(e.getMessage());
        }
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
