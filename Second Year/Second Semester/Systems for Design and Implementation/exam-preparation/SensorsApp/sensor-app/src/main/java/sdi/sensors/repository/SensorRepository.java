package sdi.sensors.repository;

import sdi.sensors.domain.Sensor;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.List;
import java.util.Optional;

@org.springframework.stereotype.Repository
public class SensorRepository implements Repository<Integer, Sensor> {
    private final JdbcOperations jdbcOperations;

    public SensorRepository(JdbcOperations jdbcOperations) {
        this.jdbcOperations = jdbcOperations;
    }

    @Override
    public List<Sensor> findAll() {
        String queryString = "select * from SensorData";
        return jdbcOperations.query(queryString, (rs, i) -> {
            Integer id = rs.getInt("id");
            String name = rs.getString("name");
            Double lowerBound = rs.getDouble("lower_bound");
            Double upperBound = rs.getDouble("upper_bound");

            return new Sensor(id, name, lowerBound, upperBound);
        });
    }

    @Override
    public Optional<Sensor> findById(Integer id) {
        try {
            String queryString = "select * from SensorData where id = ?";
            var sensor = jdbcOperations.queryForObject(queryString, new Object[]{id}, (rs, i) -> {
                Integer sensorId = rs.getInt("id");
                String name = rs.getString("name");
                Double lowerBound = rs.getDouble("lower_bound");
                Double upperBound = rs.getDouble("upper_bound");

                return new Sensor(sensorId, name, lowerBound, upperBound);
            });

            return Optional.ofNullable(sensor);
        } catch (EmptyResultDataAccessException e) {
            return Optional.empty();
        }
    }

    @Override
    public Optional<Sensor> findByName(String name) {
        try {
            String queryString = "select * from SensorData where name = ?";
            var sensor = jdbcOperations.queryForObject(queryString, new Object[]{name}, (rs, i) -> {
                Integer id = rs.getInt("id");
                String sensorName = rs.getString("name");
                Double lowerBound = rs.getDouble("lower_bound");
                Double upperBound = rs.getDouble("upper_bound");

                return new Sensor(id, sensorName, lowerBound, upperBound);
            });

            return Optional.ofNullable(sensor);
        } catch (EmptyResultDataAccessException e) {
            return Optional.empty();
        }
    }

    @Override
    public void save(Sensor entity) {
        String queryString = "insert into SensorData(id, name, lower_bound, upper_bound) values (?, ?, ?, ?)";
        jdbcOperations.update(queryString, entity.getId(), entity.getName(), entity.getLowerBound(), entity.getUpperBound());
    }
}
