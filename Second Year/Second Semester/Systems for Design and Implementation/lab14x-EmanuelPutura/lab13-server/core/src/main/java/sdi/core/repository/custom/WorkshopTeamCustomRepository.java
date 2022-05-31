package sdi.core.repository.custom;

import sdi.core.model.entities.WorkshopTeam;

import java.util.List;

public interface WorkshopTeamCustomRepository {
    List<WorkshopTeam> getWorkshopTeamsWithTeamName(String teamName);
    List<WorkshopTeam> getWorkshopTeamsWithEmptyTeamName();
}
