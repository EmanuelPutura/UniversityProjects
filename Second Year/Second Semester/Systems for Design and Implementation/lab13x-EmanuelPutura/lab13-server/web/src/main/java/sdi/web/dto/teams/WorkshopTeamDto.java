package sdi.web.dto.teams;

import lombok.*;
import sdi.web.dto.BaseDto;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class WorkshopTeamDto extends BaseDto {
    private String teamName;
    private Long technicianId;
}
