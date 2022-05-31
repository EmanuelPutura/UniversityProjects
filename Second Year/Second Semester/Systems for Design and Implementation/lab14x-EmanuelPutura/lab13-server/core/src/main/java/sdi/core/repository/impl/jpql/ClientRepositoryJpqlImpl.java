package sdi.core.repository.impl.jpql;

import sdi.core.model.entities.Client;
import sdi.core.repository.custom.ClientCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

public class ClientRepositoryJpqlImpl extends CustomRepositorySupport implements ClientCustomRepository {
    private List<Client> getClientsWithFieldEqualTo(String field, String value, String queryString) {
        var entityManager = getEntityManager();

        var query = entityManager.createQuery(
                queryString, Client.class
        );
        query.setParameter(field, value);

        return query.getResultList();
    }

    @Override
    public List<Client> getClientsWithFirstName(String firstName) {
        String queryString = "select distinct r from Client r where r.firstName = :firstName";
        return getClientsWithFieldEqualTo("firstName", firstName, queryString);
    }

    @Override
    public List<Client> getClientsWithLastName(String lastName) {
        String queryString = "select distinct r from Client r where r.lastName = :lastName";
        return getClientsWithFieldEqualTo("lastName", lastName, queryString);
    }
}
