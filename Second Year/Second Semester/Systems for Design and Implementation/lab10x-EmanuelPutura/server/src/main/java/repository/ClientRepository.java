package repository;

import domain.entities.Client;
import org.springframework.jdbc.core.JdbcOperations;

import java.util.List;

@org.springframework.stereotype.Repository
public class ClientRepository implements Repository<Long, Client> {
    private final JdbcOperations jdbcOperations;

    public ClientRepository(JdbcOperations jdbcOperations) {
        this.jdbcOperations = jdbcOperations;
    }

    @Override
    public List<Client> findAll() {
        String queryString = "select * from client";
        return jdbcOperations.query(queryString, (rs, i) -> {
            Long id = rs.getLong("id");
            String firstName = rs.getString("first_name");
            String lastName = rs.getString("last_name");
            String phoneNumber = rs.getString("phone_number");
            String emailAddress = rs.getString("email_address");
            String homeAddress = rs.getString("home_address");

            return new Client(id, firstName, lastName, phoneNumber, emailAddress, homeAddress);
        });
    }

    @Override
    public void save(Client entity) {
        String queryString = "insert into client(id, first_name, last_name, phone_number, email_address, home_address) " +
                "values (?, ?, ?, ?, ?, ?)";
        jdbcOperations.update(queryString, entity.getId(), entity.getFirstName(), entity.getLastName(), entity.getPhoneNumber(), entity.getEmailAddress(), entity.getHomeAddress());
    }

    @Override
    public void update(Client entity) {
        String queryString = "update client " +
                "set first_name = ?, last_name = ?, phone_number = ?, email_address = ?, home_address = ? where id = ?";
        var res = jdbcOperations.update(queryString, entity.getFirstName(), entity.getLastName(), entity.getPhoneNumber(), entity.getEmailAddress(), entity.getHomeAddress(), entity.getId());
    }

    @Override
    public void deleteById(Long id) {
        String queryString = "delete from client where id = ?";
        jdbcOperations.update(queryString, id);
    }
}
