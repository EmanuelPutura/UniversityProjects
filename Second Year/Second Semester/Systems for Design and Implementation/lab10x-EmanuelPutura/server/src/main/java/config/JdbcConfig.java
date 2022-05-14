package config;

import org.apache.commons.dbcp2.BasicDataSource;
import org.postgresql.Driver;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.jdbc.core.JdbcOperations;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

@Configuration
public class JdbcConfig {
    @Bean
    JdbcOperations jdbcOperations() {
        JdbcTemplate jdbcTemplate = new JdbcTemplate();
        jdbcTemplate.setDataSource(this.dataSource());
        return jdbcTemplate;
    }

    private DataSource dataSource() {
        BasicDataSource dataSource = new BasicDataSource();
        dataSource.setDriverClassName(Driver.class.getName());

        Properties properties = new Properties();
        try {
            FileInputStream fileInputStream = new FileInputStream("gradle.properties");
            properties.load(fileInputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }

        dataSource.setUsername(properties.getProperty("database.username"));
        dataSource.setPassword(properties.getProperty("database.password"));
        dataSource.setUrl(properties.getProperty("database.url"));

        dataSource.setInitialSize(5);
        return dataSource;
    }
}
