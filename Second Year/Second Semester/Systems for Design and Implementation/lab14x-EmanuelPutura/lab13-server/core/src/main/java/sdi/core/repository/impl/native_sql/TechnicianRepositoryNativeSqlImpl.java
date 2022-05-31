package sdi.core.repository.impl.native_sql;

import org.hibernate.Session;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.entities.Technician;
import sdi.core.repository.custom.TechnicianCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

public class TechnicianRepositoryNativeSqlImpl extends CustomRepositorySupport implements TechnicianCustomRepository {
    @Override
    @Transactional
    public List<Technician> getTechniciansWithFirstName(String firstName) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from Technician r where r.firstName = :firstName",
                Technician.class
        );
        query.setParameter("firstName", firstName);

        return query.getResultList();
    }

    @Override
    @Transactional
    public List<Technician> getTechniciansWithLastName(String lastName) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from Technician r where r.lastName = :lastName",
                Technician.class
        );
        query.setParameter("lastName", lastName);

        return query.getResultList();
    }
}
