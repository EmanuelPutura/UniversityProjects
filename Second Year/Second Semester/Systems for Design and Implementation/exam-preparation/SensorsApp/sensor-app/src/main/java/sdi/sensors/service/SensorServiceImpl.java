package sdi.sensors.service;

import sdi.sensors.domain.Sensor;
import sdi.sensors.exceptions.ConnectionException;
import sdi.sensors.repository.SensorRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;

@Service
public class SensorServiceImpl implements SensorService {
    private final SensorRepository sensorRepository;
    private final ExecutorService executorService;

    @Autowired
    public SensorServiceImpl(SensorRepository sensorRepository, ExecutorService executorService) {
        this.sensorRepository = sensorRepository;
        this.executorService = executorService;
    }

    @Override
    public Future<List<Sensor>> findAll() throws ConnectionException {
        return executorService.submit(sensorRepository::findAll);
    }

    @Override
    public Future<String> save(Sensor entity) throws ConnectionException {
        return executorService.submit(() -> {
            try {
                sensorRepository.save(entity);
            } catch (DataAccessException error) {
                System.out.println(error.toString());
                return "Error!";
            }
            return "Sensor added successfully!";
        });
    }

    @Override
    public Future<Optional<Sensor>> findByName(String name) throws ConnectionException {
        return executorService.submit(() -> sensorRepository.findByName(name));
    }
}
