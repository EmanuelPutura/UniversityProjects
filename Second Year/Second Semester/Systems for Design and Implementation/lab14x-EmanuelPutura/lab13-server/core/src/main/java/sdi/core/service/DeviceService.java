package sdi.core.service;

import sdi.core.model.entities.Device;
import sdi.core.model.entities.Technician;

import java.util.List;

public interface DeviceService extends GenericService<Long, Device> {
    List<Device> findDevicesByClientId(Long clientId);

    void addTechnician(Long id, Technician technician);

    void removeTechnician(Long id, Technician technician);

    List<Device> findDevicesBeingWorkedOnByTechnician(Technician technician);
}
