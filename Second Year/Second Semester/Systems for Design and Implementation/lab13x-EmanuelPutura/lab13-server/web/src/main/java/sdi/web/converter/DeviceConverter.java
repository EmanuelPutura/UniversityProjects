package sdi.web.converter;

import sdi.core.model.entities.Client;
import sdi.web.dto.device.DeviceDto;
import sdi.core.model.entities.Device;
import org.springframework.stereotype.Component;
import sdi.web.dto.device.DeviceInsertDto;

import java.util.Collection;
import java.util.Set;
import java.util.stream.Collectors;

@Component
public class DeviceConverter extends BaseConverter<Device, DeviceDto> {
    public DeviceDto convertDeviceInsertDtoToDeviceDto(DeviceInsertDto deviceInsertDto, Client client) {
        if (!client.getId().equals(deviceInsertDto.getClientId()))
            return null;

        var deviceDto = new DeviceDto(deviceInsertDto.getType(), deviceInsertDto.getBrand(), deviceInsertDto.getModel(), client);
        deviceDto.setId(deviceInsertDto.getId());

        return deviceDto;
    }

    public DeviceInsertDto convertModelToDeviceInsertDto(Device device) {
        var deviceInsertDto = new DeviceInsertDto(device.getType(), device.getBrand(), device.getModel(), device.getClient().getId());
        deviceInsertDto.setId(device.getId());
        return deviceInsertDto;
    }

    public Set<DeviceInsertDto> convertModelToDeviceInsertDtos(Collection<Device> devices) {
        return devices.stream()
                .map(this::convertModelToDeviceInsertDto)
                .collect(Collectors.toSet());
    }

    @Override
    public Device convertDtoToModel(DeviceDto dto) {
        var model = new Device();

        model.setId(dto.getId());
        model.setType(dto.getType());
        model.setBrand(dto.getBrand());
        model.setModel(dto.getModel());
        model.setClient(dto.getClient());

        return model;
    }

    @Override
    public DeviceDto convertModelToDto(Device device) {
        DeviceDto dto = new DeviceDto(device.getType(), device.getBrand(), device.getModel(), device.getClient());
        dto.setId(device.getId());
        return dto;
    }
}
