package repository;

import domain.entities.RepairOrder;
import domain.entities.Technician;
import org.springframework.jdbc.core.JdbcOperations;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

@org.springframework.stereotype.Repository
public class RepairOrderRepository implements Repository<Long, RepairOrder> {
    private final JdbcOperations jdbcOperations;

    public RepairOrderRepository(JdbcOperations jdbcOperations) {
        this.jdbcOperations = jdbcOperations;
    }

    public List<Technician> findAllTechnicianWorkingOnDevice(Long deviceId) {
        String queryString = "select T.id, T.first_name, T.last_name, T.salary, T.phone_number, T.email_address, T.street_address, " +
                "T.employee_number from repair_order RO INNER JOIN technician T on RO.technician_id = T.id WHERE RO.device_id = ?";
        return jdbcOperations.query(queryString, ps -> ps.setLong(1, deviceId), (rs, i) -> {
            Long id = rs.getLong("id");
            String firstName = rs.getString("first_name");
            String lastName = rs.getString("last_name");
            Long salary = rs.getLong("salary");
            String phoneNumber = rs.getString("phone_number");
            String emailAddress = rs.getString("email_address");
            String street_address = rs.getString("street_address");
            Long employee_number = rs.getLong("employee_number");

            return new Technician(id, firstName, lastName, salary, phoneNumber, emailAddress, street_address, employee_number);
        });
    }

    @Override
    public List<RepairOrder> findAll() {
        String queryString = "select * from repair_order";
        return jdbcOperations.query(queryString, (rs, i) -> {
            Long id = rs.getLong("id");
            Long deviceId = rs.getLong("device_id");
            Long technicianId = rs.getLong("technician_id");
            Date dateBrought = rs.getDate("date_brought");
            Date dateExpected = rs.getDate("date_expected");
            Long cost = rs.getLong("cost");

            return new RepairOrder(id, deviceId, technicianId, dateBrought.toString(), dateExpected.toString(), cost);
        });
    }

    @Override
    public void save(RepairOrder entity) {
        String queryString = "insert into repair_order(id, device_id, technician_id, date_brought, date_expected, cost) " +
                "values (?, ?, ?, ?, ?, ?)";

        DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
            var dateBrought = new Date(dateFormat.parse(entity.getDateBrought()).getTime());
            var dateExpected = new Date(dateFormat.parse(entity.getDateExpected()).getTime());

            jdbcOperations.update(queryString, entity.getId(), entity.getDeviceID(), entity.getTechnicianID(), dateBrought, dateExpected, entity.getCost());
        } catch (ParseException ignored) {
        }
    }

    @Override
    public void update(RepairOrder entity) {
        String queryString = "update repair_order " +
                "set device_id = ?, technician_id = ?, date_brought = ?, date_expected = ?, cost = ? where id = ?";

        DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
        try {
            var dateBrought = new Date(dateFormat.parse(entity.getDateBrought()).getTime());
            var dateExpected = new Date(dateFormat.parse(entity.getDateExpected()).getTime());

            jdbcOperations.update(queryString, entity.getDeviceID(), entity.getTechnicianID(), dateBrought, dateExpected, entity.getCost(), entity.getId());
        } catch (ParseException ignored) {
        }
    }

    @Override
    public void deleteById(Long id) {
        String queryString = "delete from repair_order where id = ?";
        jdbcOperations.update(queryString, id);
    }
}
