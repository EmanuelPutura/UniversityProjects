package sdi.core.repository.impl.native_sql;

import org.hibernate.Session;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.entities.Client;
import sdi.core.repository.custom.ClientCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("ClientRepositoryNativeSqlImpl")
public class ClientRepositoryNativeSqlImpl extends CustomRepositorySupport implements ClientCustomRepository {
    @Override
    @Transactional
    public List<Client> getClientWithFirstName(String firstName) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from Client r where r.firstName = :firstName",
                Client.class
        );
        query.setParameter("firstName", firstName);

        return query.getResultList();
    }

    @Override
    @Transactional
    public List<Client> getClientWithLastName(String lastName) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from Client r where r.lastName = :lastName",
                Client.class
        );
        query.setParameter("lastName", lastName);

        return query.getResultList();
    }
}
