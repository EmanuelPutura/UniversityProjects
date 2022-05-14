package repository;

import domain.entities.Device;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.JdbcOperations;
import org.springframework.jdbc.core.PreparedStatementCreator;

import java.util.List;

@org.springframework.stereotype.Repository
public class DeviceRepository implements Repository<Long, Device> {
    private final JdbcOperations jdbcOperations;

    public DeviceRepository(JdbcOperations jdbcOperations) {
        this.jdbcOperations = jdbcOperations;
    }

    @Override
    public List<Device> findAll() {
        String queryString = "select * from device";
        return jdbcOperations.query(queryString, (rs, i) -> {
            Long id = rs.getLong("id");
            String type = rs.getString("type");
            String brand = rs.getString("brand");
            String model = rs.getString("model");
            Long client_id = rs.getLong("client_id");

            return new Device(id, type, brand, model, client_id);
        });
    }

    @Override
    public void save(Device entity) {
        String queryString = "insert into device(id, type, brand, model, client_id) " +
                "values (?, ?, ?, ?, ?)";

        jdbcOperations.update(queryString, entity.getId(), entity.getType(), entity.getBrand(), entity.getModel(), entity.getClientID());
    }

    @Override
    public void update(Device entity) {
        String queryString = "update device " +
                "set type = ?, brand = ?, model = ?, client_id = ? where id = ?";
        jdbcOperations.update(queryString, entity.getType(), entity.getBrand(), entity.getModel(), entity.getClientID(), entity.getId());
    }

    @Override
    public void deleteById(Long id) {
        String queryString = "delete from device where id = ?";
        jdbcOperations.update(queryString, id);
    }

    public List<Device> searchByClientId(Long clientId) {
        String queryString = "select * from device where client_id = ?";
        return jdbcOperations.query(queryString, ps -> ps.setLong(1, clientId), (rs, i) -> {
            Long id = rs.getLong("id");
            String type = rs.getString("type");
            String brand = rs.getString("brand");
            String model = rs.getString("model");
            Long client_id = rs.getLong("client_id");

            return new Device(id, type, brand, model, client_id);
        });
    }
}
