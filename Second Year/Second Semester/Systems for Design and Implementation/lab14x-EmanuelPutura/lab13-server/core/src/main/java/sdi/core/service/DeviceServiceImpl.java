package sdi.core.service;

import org.springframework.data.domain.PageRequest;
import sdi.core.model.entities.Device;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.entities.Technician;
import sdi.core.repository.DeviceRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class DeviceServiceImpl implements DeviceService {
    private final DeviceRepository repository;

    @Autowired
    public DeviceServiceImpl(DeviceRepository repository) {
        this.repository = repository;
    }

    public List<Device> findDevicesByClientId(Long clientId) {
        return repository.findDeviceByClientId(clientId);
    }

    @Override
    @Transactional
    public void addTechnician(Long id, Technician technician) {
        var device = search(id);
        if (device.isEmpty())
            return;

        device.get().getAssignedTechnicians().add(technician);
    }

    @Override
    @Transactional
    public void removeTechnician(Long id, Technician technician) {
        var device = search(id);
        if (device.isEmpty())
            return;

        device.get().getAssignedTechnicians().remove(technician);
    }

    @Override
    public List<Device> findDevicesBeingWorkedOnByTechnician(Technician technician) {
        var devices = new ArrayList<Device>();
        repository.findAllWithTechnicians().forEach((device -> {
            if (device.getAssignedTechnicians().contains(technician))
                devices.add(device);
        }));

        return devices;
    }

    @Override
    public List<Device> getAll() {
        List<Device> resultList = new ArrayList<>();
        repository.findAll().forEach(resultList::add);

        return resultList;
    }

    @Override
    public List<Device> getAllFromPage(int pageNumber, int pageSize) {
        List<Device> resultList = new ArrayList<>();
        repository.findAll(PageRequest.of(pageNumber, pageSize)).forEach(resultList::add);

        return resultList;
    }

    @Override
    public Device save(Device entity) {
        return repository.save(entity);
    }

    @Override
    @Transactional
    public Device update(Device entity) {
        var updatedDevice = repository.findById(entity.getId()).orElseThrow();
        updatedDevice.setType(entity.getType());
        updatedDevice.setBrand(entity.getBrand());
        updatedDevice.setModel(entity.getModel());
        updatedDevice.setClient(entity.getClient());

        return updatedDevice;
    }

    @Override
    public Optional<Device> search(Long id) {
        return repository.findById(id);
    }

    @Override
    public void delete(Long id) {
        repository.deleteById(id);
    }
}
