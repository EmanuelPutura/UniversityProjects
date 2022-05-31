package sdi.web.dto.technician;

import lombok.*;
import sdi.web.dto.BaseDto;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class TechnicianDto extends BaseDto {
    private String firstName;
    private String lastName;
    private Long salary;
}
