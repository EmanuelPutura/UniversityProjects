package sdi.core.repository.impl.criteria;

import sdi.core.model.entities.WorkshopTeam;
import sdi.core.repository.custom.WorkshopTeamCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

public class WorkshopTeamRepositoryCriteriaImpl extends CustomRepositorySupport implements WorkshopTeamCustomRepository {
    private List<WorkshopTeam> getWorkshopTeamsHavingFieldEqualTo(String fieldName, String value) {
        var entityManager = getEntityManager();
        var criteriaBuilder = entityManager.getCriteriaBuilder();

        var query = criteriaBuilder.createQuery(WorkshopTeam.class);
        query.distinct(true);

        var root = query.from(WorkshopTeam.class);
        query.where(criteriaBuilder.equal(root.get(fieldName), value));

        return entityManager.createQuery(query).getResultList();
    }

    @Override
    public List<WorkshopTeam> getWorkshopTeamsWithTeamName(String teamName) {
        return getWorkshopTeamsHavingFieldEqualTo("teamName", teamName);
    }

    @Override
    public List<WorkshopTeam> getWorkshopTeamsWithEmptyTeamName() {
        return getWorkshopTeamsHavingFieldEqualTo("teamName", "");
    }
}
