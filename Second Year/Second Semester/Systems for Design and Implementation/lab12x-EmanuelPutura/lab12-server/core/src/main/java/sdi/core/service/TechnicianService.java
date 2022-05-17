package sdi.core.service;

import sdi.core.model.entities.Device;
import sdi.core.model.entities.Technician;

import java.util.List;

public interface TechnicianService extends GenericService<Long, Technician> {
    void addDevice(Long id, Device device);

    void removeDevice(Long id, Device device);

    List<Technician> findTechniciansWorkingOnDevice(Device device);
}
