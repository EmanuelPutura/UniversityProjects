package sdi.core.repository.custom;

import sdi.core.model.entities.Device;

import java.util.List;

public interface DeviceCustomRepository {
    List<Device> getDeviceByType(String type);
    List<Device> getDeviceByBrand(String brand);
}
