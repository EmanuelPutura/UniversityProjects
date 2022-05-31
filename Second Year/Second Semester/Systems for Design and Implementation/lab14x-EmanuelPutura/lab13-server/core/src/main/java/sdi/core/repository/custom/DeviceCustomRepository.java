package sdi.core.repository.custom;

import sdi.core.model.entities.Device;

import java.util.List;

public interface DeviceCustomRepository {
    List<Device> getDevicesWithType(String type);
    List<Device> getDevicesWithBrand(String brand);
}
