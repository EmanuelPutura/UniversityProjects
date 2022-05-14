package sdi.web.dto.device;

import lombok.*;
import sdi.core.model.entities.Client;
import sdi.web.dto.BaseDto;
import sdi.web.dto.client.ClientDto;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class DeviceDto extends BaseDto {
    private String type;
    private String brand;
    private String model;
    private Client client;
}
