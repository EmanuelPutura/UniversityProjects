package web.lab9.assignment9.repository;

import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.utils.DatabasePropertiesRetriever;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public abstract class GenericRepository<PK, T> implements Repository<PK, T> {
    protected String databaseUrl = "";
    protected String databaseUsername = "";
    protected String databasePassword = "";

    protected final String relationName;
    protected final String primaryKeyName;

    @Override
    public List<T> findAll() throws AppException {
        String selectAllQuery = String.format("SELECT * FROM %s", relationName);
        List<T> entities = new ArrayList<>();

        try (
                var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
                var statement = connection.prepareStatement(selectAllQuery);
                var resultSet = statement.executeQuery()
        ) {
            Optional<T> optional = getEntityFromResultSet(resultSet);
            while(optional.isPresent()){
                entities.add(optional.get());
                optional = getEntityFromResultSet(resultSet);
            }
        } catch (SQLException e) {
            throw new AppException(e.getMessage());
        }
        return entities;
    }

    @Override
    public Optional<T> findOneByPrimaryKey(PK id) throws AppException {
        String selectOneQuery = String.format("SELECT * FROM %s WHERE %s = ?", relationName, primaryKeyName);

        try (
            var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
            var statement = connection.prepareStatement(selectOneQuery)
        ) {
            statement.setString(1, id.toString());

            try (
                var resultSet = statement.executeQuery()
            ) {
                return getEntityFromResultSet(resultSet);
            }
        } catch (SQLException e) {
            throw new AppException(e.getMessage());
        }
    }

    protected GenericRepository(String configFilePath, String relationName, String primaryKeyName) throws AppException {
        try {
            Class.forName("org.postgresql.Driver");  // load driver
        } catch (ClassNotFoundException e) {
            throw new AppException(e.getMessage());
        }

        this.primaryKeyName = primaryKeyName;
        this.relationName = relationName;

        var databaseProperties = DatabasePropertiesRetriever.getProperties(configFilePath);
        databaseProperties.ifPresent(properties -> {
            this.databaseUrl = properties.getDbUrl();
            this.databaseUsername = properties.getDbUsername();
            this.databasePassword = properties.getDbPassword();
        });
    }

    protected abstract Optional<T> getEntityFromResultSet(ResultSet resultSet);
}
