package service;

import domain.entities.Device;
import domain.exceptions.ConnectionException;
import domain.exceptions.ValidatorException;
import domain.validators.DeviceValidator;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;
import repository.DeviceRepository;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class DeviceServiceImpl implements DeviceService {
    private final DeviceRepository deviceRepository;
    private final ExecutorService executorService;
    private final DeviceValidator deviceValidator;

    public DeviceServiceImpl(DeviceRepository deviceRepository, ExecutorService executorService) {
        this.deviceRepository = deviceRepository;
        this.executorService = executorService;

        this.deviceValidator = new DeviceValidator();
    }

    @Override
    public Future<List<Device>> findAll() throws ConnectionException {
        return executorService.submit(deviceRepository::findAll);
    }

    @Override
    public Future<String> save(Device entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                deviceValidator.validate(entity);
                deviceRepository.save(entity);
            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Device added successfully!";
        });
    }

    @Override
    public Future<String> update(Device entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                deviceValidator.validate(entity);
                deviceRepository.update(entity);

            } catch (ValidatorException | DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Device updated successfully!";
        });
    }

    @Override
    public Future<String> deleteById(Long id) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                deviceRepository.deleteById(id);
            } catch (DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }

            return "Device deleted successfully!";
        });
    }

    public Future<List<Device>> searchByClientId(Long clientId) {
        return executorService.submit(() -> {
            return deviceRepository.searchByClientId(clientId);
        });
    }
}
