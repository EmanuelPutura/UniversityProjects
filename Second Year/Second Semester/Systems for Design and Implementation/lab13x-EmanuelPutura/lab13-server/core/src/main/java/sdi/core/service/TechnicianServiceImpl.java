package sdi.core.service;

import sdi.core.model.entities.Device;
import sdi.core.model.entities.Technician;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.repository.TechnicianRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class TechnicianServiceImpl implements TechnicianService {
    private final TechnicianRepository repository;

    @Autowired
    public TechnicianServiceImpl(TechnicianRepository repository) {
        this.repository = repository;
    }

    @Override
    public List<Technician> getAll() {
        List<Technician> resultList = new ArrayList<>();
        repository.findAll().forEach(resultList::add);

        return resultList;
    }

    @Override
    public Technician save(Technician entity) {
        return repository.save(entity);
    }

    @Override
    @Transactional
    public Technician update(Technician entity) {
        var updatedTechnician = repository.findById(entity.getId()).orElseThrow();
        updatedTechnician.setFirstName(entity.getFirstName());
        updatedTechnician.setLastName(entity.getLastName());
        updatedTechnician.setSalary(entity.getSalary());

        return updatedTechnician;
    }

    @Override
    public Optional<Technician> search(Long id) {
        return repository.findById(id);
    }

    @Override
    public void delete(Long id) {
        repository.deleteById(id);
    }

    @Override
    @Transactional
    public void addDevice(Long id, Device device) {
        var technician = search(id);
        if (technician.isEmpty())
            return;

        technician.get().getRepairedDevices().add(device);
    }

    @Override
    @Transactional
    public void removeDevice(Long id, Device device) {
        var technician = search(id);
        if (technician.isEmpty())
            return;

        technician.get().getRepairedDevices().remove(device);
    }

    @Override
    @Transactional
    public List<Technician> findTechniciansWorkingOnDevice(Device device) {
        var technicians = new ArrayList<Technician>();
        repository.findAll().forEach((technician -> {
            if (technician.getRepairedDevices().contains(device))
                technicians.add(technician);
        }));

        return technicians;
    }
}
