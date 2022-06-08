package sdi.sensors.config;

import org.apache.commons.dbcp2.BasicDataSource;
import org.postgresql.Driver;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.jdbc.core.JdbcOperations;
import org.springframework.jdbc.core.JdbcTemplate;

import javax.sql.DataSource;

@Configuration
public class JdbcConfiguration {
    @Bean
    JdbcOperations jdbcOperations() {
        JdbcTemplate jdbcTemplate = new JdbcTemplate();
        jdbcTemplate.setDataSource(this.dataSource());
        return jdbcTemplate;
    }

    private DataSource dataSource() {
        BasicDataSource dataSource = new BasicDataSource();
        dataSource.setDriverClassName(Driver.class.getName());

        dataSource.setUsername("postgres");
        dataSource.setPassword("postgres");
        dataSource.setUrl("jdbc:postgresql://localhost:5432/mpp-ex2");

        dataSource.setInitialSize(5);
        return dataSource;
    }
}
