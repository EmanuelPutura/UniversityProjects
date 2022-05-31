package sdi.core.repository;

import sdi.core.model.entities.Device;

import java.util.List;

public interface DeviceRepository extends CatalogRepository<Device, Long>{
    List<Device> findDeviceByClientId(Long clientId);
}
