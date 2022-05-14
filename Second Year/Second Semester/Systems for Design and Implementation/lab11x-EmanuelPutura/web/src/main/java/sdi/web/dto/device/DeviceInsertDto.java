package sdi.web.dto.device;

import lombok.*;
import sdi.core.model.entities.Client;
import sdi.web.dto.BaseDto;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class DeviceInsertDto extends BaseDto {
    private String type;
    private String brand;
    private String model;
    private Long clientId;
}
