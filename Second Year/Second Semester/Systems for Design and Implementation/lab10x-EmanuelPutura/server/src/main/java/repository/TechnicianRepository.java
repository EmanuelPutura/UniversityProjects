package repository;

import domain.entities.Client;
import domain.entities.Technician;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.List;

@org.springframework.stereotype.Repository
public class TechnicianRepository implements Repository<Long, Technician> {
    private final JdbcOperations jdbcOperations;

    public TechnicianRepository(JdbcOperations jdbcOperations) {
        this.jdbcOperations = jdbcOperations;
    }

    @Override
    public List<Technician> findAll() {
        String queryString = "select * from technician";
        return jdbcOperations.query(queryString, (rs, i) -> {
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
    public void save(Technician entity) {
        String queryString = "insert into technician(id, first_name, last_name, salary, phone_number, email_address, street_address, employee_number) " +
                "values (?, ?, ?, ?, ?, ?, ?, ?)";
        jdbcOperations.update(queryString, entity.getId(), entity.getFirstName(), entity.getLastName(), entity.getSalary(), entity.getPhoneNumber(), entity.getEmailAddress(), entity.getHomeAddress(), entity.getEmployeeNumber());
    }

    @Override
    public void update(Technician entity) {
        String queryString = "update technician " +
                "set first_name = ?, last_name = ?, salary = ?, phone_number = ?, email_address = ?, street_address = ?, employee_number = ? where id = ?";
        jdbcOperations.update(queryString, entity.getFirstName(), entity.getLastName(), entity.getSalary(), entity.getPhoneNumber(), entity.getEmailAddress(), entity.getHomeAddress(), entity.getEmployeeNumber(), entity.getId());
    }

    @Override
    public void deleteById(Long id) {
        String queryString = "delete from technician where id = ?";
        jdbcOperations.update(queryString, id);
    }
}
