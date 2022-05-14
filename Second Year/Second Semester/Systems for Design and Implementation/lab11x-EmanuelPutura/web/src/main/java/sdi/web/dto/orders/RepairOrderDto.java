package sdi.web.dto.orders;

import lombok.*;
import sdi.web.dto.BaseDto;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class RepairOrderDto extends BaseDto {
    private Long technicianId;
    private Long deviceId;
}
