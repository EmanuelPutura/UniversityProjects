package sdi.web.dto.device;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class DeviceInsertDtos {
    private Set<DeviceInsertDto> devices;
}

