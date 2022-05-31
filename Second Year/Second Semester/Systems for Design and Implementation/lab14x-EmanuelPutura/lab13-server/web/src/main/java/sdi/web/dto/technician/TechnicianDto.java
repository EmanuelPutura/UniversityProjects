package sdi.web.dto.technician;

import lombok.*;
import sdi.web.dto.BaseDto;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class TechnicianDto extends BaseDto {
    private String firstName;
    private String lastName;
    private Long salary;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || TechnicianDto.class != o.getClass()) return false;
        TechnicianDto dto = (TechnicianDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
