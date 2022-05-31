package sdi.web.dto.teams;

import lombok.*;
import sdi.web.dto.BaseDto;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class WorkshopTeamDto extends BaseDto {
    private String teamName;
    private Long technicianId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || WorkshopTeamDto.class != o.getClass()) return false;
        WorkshopTeamDto dto = (WorkshopTeamDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
