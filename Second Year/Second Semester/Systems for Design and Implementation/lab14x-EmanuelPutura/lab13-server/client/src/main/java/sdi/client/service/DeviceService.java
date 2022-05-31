package sdi.client.service;

import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;
import sdi.core.model.entities.Device;
import sdi.web.dto.device.DeviceInsertDto;
import sdi.web.dto.device.DevicesInsertDto;

import java.util.ArrayList;
import java.util.List;

@Service
public class DeviceService implements CrudService<DeviceInsertDto> {
    private final String DEVICE_API_URL = "http://localhost:8080/api/devices";
    private final RestTemplate restTemplate;

    public DeviceService(RestTemplate restTemplate) {
        this.restTemplate = restTemplate;
    }

    public List<DeviceInsertDto> searchByClientId(Long id) {
        DevicesInsertDto devicesDto = restTemplate.getForObject(DEVICE_API_URL + "/forClient?deviceId={deviceId}", DevicesInsertDto.class, id);
        if (devicesDto == null || devicesDto.getDevices() == null)
            return null;

        return new ArrayList<>(devicesDto.getDevices());
    }

    @Override
    public List<DeviceInsertDto> getAll() {
        DevicesInsertDto devicesDto = restTemplate.getForObject(DEVICE_API_URL, DevicesInsertDto.class);

        if (devicesDto == null || devicesDto.getDevices() == null)
            return null;

        return new ArrayList<>(devicesDto.getDevices());
    }

    @Override
    public DeviceInsertDto save(DeviceInsertDto entity) {
        return restTemplate.postForObject(DEVICE_API_URL, entity, DeviceInsertDto.class);
    }

    @Override
    public DeviceInsertDto update(DeviceInsertDto entity) {
        restTemplate.put(DEVICE_API_URL + "/{id}", entity, entity.getId());
        return restTemplate.getForObject(DEVICE_API_URL, DeviceInsertDto.class);
    }

    @Override
    public void deleteById(Long id) {
        restTemplate.delete(DEVICE_API_URL + "/{id}", id);
    }
}
