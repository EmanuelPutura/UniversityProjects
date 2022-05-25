package sdi.web.dto.device;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import sdi.core.model.entities.Client;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class DeviceWithClientFieldsDto {
    private String type;
    private String brand;
    private String model;
    private String clientLastName;
    private String clientFirstName;
    private String clientEmailAddress;
}
