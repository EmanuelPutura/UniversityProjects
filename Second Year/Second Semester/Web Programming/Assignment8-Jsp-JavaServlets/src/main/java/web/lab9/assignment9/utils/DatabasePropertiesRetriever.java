package web.lab9.assignment9.utils;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Optional;
import java.util.Properties;

public class DatabasePropertiesRetriever {
    public static Optional<DatabaseProperties> getProperties(String propertiesFilePath) {
        Properties properties = new Properties();
        try {
            FileInputStream fileInputStream = new FileInputStream(propertiesFilePath);
            properties.load(fileInputStream);

            return Optional.of(new DatabaseProperties(properties.getProperty("db.jdbcUrl"), properties.getProperty("db.username"), properties.getProperty("db.password")));
        } catch (IOException e) {
            return Optional.empty();
        }
    }
}
