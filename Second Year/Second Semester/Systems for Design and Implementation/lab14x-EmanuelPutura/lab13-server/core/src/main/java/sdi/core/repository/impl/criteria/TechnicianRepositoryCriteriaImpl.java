package sdi.core.repository.impl.criteria;

import sdi.core.model.entities.Technician;
import sdi.core.repository.custom.TechnicianCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

public class TechnicianRepositoryCriteriaImpl extends CustomRepositorySupport implements TechnicianCustomRepository {
    private List<Technician> getTechniciansHavingFieldEqualTo(String fieldName, String value) {
        var entityManager = getEntityManager();
        var criteriaBuilder = entityManager.getCriteriaBuilder();

        var query = criteriaBuilder.createQuery(Technician.class);
        query.distinct(true);

        var root = query.from(Technician.class);
        query.where(criteriaBuilder.equal(root.get(fieldName), value));

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<Technician> getTechnicianByFirstName(String firstName) {
        return getTechniciansHavingFieldEqualTo("firstName", firstName);
    }

    @Override
    public List<Technician> getTechnicianByLastName(String lastName) {
        return getTechniciansHavingFieldEqualTo("lastName", lastName);
    }
}
