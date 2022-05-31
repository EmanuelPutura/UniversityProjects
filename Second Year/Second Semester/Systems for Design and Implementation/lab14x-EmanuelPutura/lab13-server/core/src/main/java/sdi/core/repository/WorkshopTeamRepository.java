package sdi.core.repository;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import sdi.core.model.entities.WorkshopTeam;
import sdi.core.repository.custom.WorkshopTeamCustomRepository;

import java.util.List;

public interface WorkshopTeamRepository extends CatalogRepository<WorkshopTeam, Long>, WorkshopTeamCustomRepository {
    @Query("select distinct wt from WorkshopTeam wt")
    @EntityGraph(value = "WorkshopTeam.teamsWithTechnician", type = EntityGraph.EntityGraphType.LOAD)
    List<WorkshopTeam> findAllWithTechnician();

    @Query("select distinct wt from WorkshopTeam wt")
    @EntityGraph(value = "WorkshopTeam.teamsWithTechnicianAndDevices", type = EntityGraph.EntityGraphType.LOAD)
    List<WorkshopTeam> findAllWithTechnicianAndDevices();
}
