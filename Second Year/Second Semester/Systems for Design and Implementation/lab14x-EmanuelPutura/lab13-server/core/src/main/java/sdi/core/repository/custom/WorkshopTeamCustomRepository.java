package sdi.core.repository.custom;

import org.springframework.data.jpa.repository.Query;
import sdi.core.model.entities.WorkshopTeam;

import java.util.List;

public interface WorkshopTeamCustomRepository {
    List<WorkshopTeam> getWorkshopTeamWithTeamName(String teamName);
}
