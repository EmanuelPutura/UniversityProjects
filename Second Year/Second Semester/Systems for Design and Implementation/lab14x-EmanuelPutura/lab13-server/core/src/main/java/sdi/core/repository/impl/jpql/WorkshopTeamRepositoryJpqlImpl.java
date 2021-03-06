package sdi.core.repository.impl.jpql;

import org.springframework.stereotype.Component;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.repository.custom.WorkshopTeamCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

@Component("WorkshopTeamRepositoryJpqlImpl")
public class WorkshopTeamRepositoryJpqlImpl extends CustomRepositorySupport implements WorkshopTeamCustomRepository {
    private List<WorkshopTeam> getClientsWithFieldEqualTo(String field, String value, String queryString) {
        var entityManager = getEntityManager();

        var query = entityManager.createQuery(
                queryString, WorkshopTeam.class
        );
        query.setParameter(field, value);

        return query.getResultList();
    }

    @Override
    public List<WorkshopTeam> getWorkshopTeamWithTeamName(String teamName) {
        String queryString = "select distinct r from WorkshopTeam r where r.teamName = :teamName";
        return getClientsWithFieldEqualTo("teamName", teamName, queryString);
    }
}
