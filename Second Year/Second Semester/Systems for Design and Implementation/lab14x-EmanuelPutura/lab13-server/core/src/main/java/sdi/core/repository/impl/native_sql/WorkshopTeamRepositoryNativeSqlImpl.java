package sdi.core.repository.impl.native_sql;

import org.hibernate.Session;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.repository.custom.WorkshopTeamCustomRepository;
import sdi.core.repository.impl.CustomRepositorySupport;

import java.util.List;

public class WorkshopTeamRepositoryNativeSqlImpl extends CustomRepositorySupport implements WorkshopTeamCustomRepository {
    @Override
    @Transactional
    public List<WorkshopTeam> getWorkshopTeamsWithTeamName(String teamName) {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from WorkshopTeam r where r.teamName = :teamName",
                WorkshopTeam.class
        );
        query.setParameter("teamName", teamName);

        return query.getResultList();
    }

    @Override
    @Transactional
    public List<WorkshopTeam> getWorkshopTeamsWithEmptyTeamName() {
        var session = getEntityManager().unwrap(Session.class);

        var query = session.createNativeQuery(
                "select distinct * from WorkshopTeam r where r.teamName = :teamName",
                WorkshopTeam.class
        );
        query.setParameter("teamName", "");

        return query.getResultList();
    }
}
