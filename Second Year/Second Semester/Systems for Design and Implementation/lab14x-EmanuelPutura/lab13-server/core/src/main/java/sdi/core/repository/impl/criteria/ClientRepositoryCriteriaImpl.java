package sdi.core.repository.impl.criteria;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.Client;
import sdi.core.repository.custom.ClientCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("ClientRepositoryCriteriaImpl")
public class ClientRepositoryCriteriaImpl extends CustomRepositorySupport implements ClientCustomRepository {
    private List<Client> getClientsHavingFieldEqualTo(String fieldName, String value) {
        var entityManager = getEntityManager();
        var criteriaBuilder = entityManager.getCriteriaBuilder();

        var query = criteriaBuilder.createQuery(Client.class);
        query.distinct(true);

        var root = query.from(Client.class);
        query.where(criteriaBuilder.equal(root.get(fieldName), value));

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Client> getClientWithFirstName(String firstName) {
        return getClientsHavingFieldEqualTo("firstName", firstName);
    }

    @Override
    public List<Client> getClientWithLastName(String lastName) {
        return getClientsHavingFieldEqualTo("lastName", lastName);
    }
}
