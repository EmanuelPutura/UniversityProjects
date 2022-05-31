package sdi.web.dto.teams;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import sdi.web.dto.client.ClientDto;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class WorkshopTeamDtos {
    private Set<WorkshopTeamDto> teams;
}
