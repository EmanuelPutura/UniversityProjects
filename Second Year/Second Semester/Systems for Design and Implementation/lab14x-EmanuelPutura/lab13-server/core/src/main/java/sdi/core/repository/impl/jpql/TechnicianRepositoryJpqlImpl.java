package sdi.core.repository.impl.jpql;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.Technician;
import sdi.core.repository.custom.TechnicianCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("TechnicianRepositoryJpqlImpl")
public class TechnicianRepositoryJpqlImpl extends CustomRepositorySupport implements TechnicianCustomRepository {
    private List<Technician> getClientsWithFieldEqualTo(String field, String value, String queryString) {
        var entityManager = getEntityManager();

        var query = entityManager.createQuery(
                queryString, Technician.class
        );
        query.setParameter(field, value);

        return query.getResultList();
    }

    @Override
    public List<Technician> getTechnicianWithFirstName(String firstName) {
        String queryString = "select distinct r from Technician r where r.firstName = :firstName";
        return getClientsWithFieldEqualTo("firstName", firstName, queryString);
    }

    @Override
    public List<Technician> getTechnicianWithLastName(String lastName) {
        String queryString = "select distinct r from Technician r where r.lastName = :lastName";
        return getClientsWithFieldEqualTo("lastName", lastName, queryString);
    }
}
