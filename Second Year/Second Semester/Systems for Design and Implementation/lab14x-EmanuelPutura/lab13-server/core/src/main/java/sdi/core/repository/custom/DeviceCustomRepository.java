package sdi.core.repository.custom;

import sdi.core.model.entities.Device;

import java.util.List;

public interface DeviceCustomRepository {
    List<Device> getDeviceWithType(String type);
    List<Device> getDeviceWithBrand(String brand);
}
