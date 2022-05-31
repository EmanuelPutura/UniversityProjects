package sdi.core.repository;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import sdi.core.model.entities.WorkshopTeam;

import java.util.List;

public interface WorkshopTeamRepository extends CatalogRepository<WorkshopTeam, Long> {
    @Query("select distinct wt from WorkshopTeam wt")
    @EntityGraph(value = "WorkshopTeam.teamsWithTechnician", type = EntityGraph.EntityGraphType.LOAD)
    List<WorkshopTeam> findAllWithTechnician();
}
