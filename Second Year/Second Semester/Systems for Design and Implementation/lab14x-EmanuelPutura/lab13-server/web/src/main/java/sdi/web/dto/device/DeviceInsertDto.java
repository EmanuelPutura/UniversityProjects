package sdi.web.dto.device;

import lombok.*;
import sdi.web.dto.BaseDto;
import sdi.web.dto.client.ClientDto;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class DeviceInsertDto extends BaseDto {
    private String type;
    private String brand;
    private String model;
    private Long clientId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || DeviceInsertDto.class != o.getClass()) return false;
        DeviceInsertDto dto = (DeviceInsertDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
