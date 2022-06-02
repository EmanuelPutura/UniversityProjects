package sdi.core.repository.impl.criteria;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.repository.custom.WorkshopTeamCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("WorkshopTeamRepositoryCriteriaImpl")
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
    public List<WorkshopTeam> getWorkshopTeamWithTeamName(String teamName) {
        return getWorkshopTeamsHavingFieldEqualTo("teamName", teamName);
    }
}
