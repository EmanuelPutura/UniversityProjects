package sdi.core.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import sdi.core.model.Sensor;
import sdi.core.model.SensorNameDto;
import sdi.core.repository.SensorRepository;

import java.util.List;

@Service
public class SensorServiceImpl implements SensorService {
    private final SensorRepository sensorRepository;

    @Autowired
    public SensorServiceImpl(SensorRepository sensorRepository) {
        this.sensorRepository = sensorRepository;
    }

    @Override
    public List<Sensor> findAll() {
        return sensorRepository.findAll();
    }

    @Override
    public List<SensorNameDto> getAllSensorNames() {
        return sensorRepository.getAllSensorNames();
    }

    @Override
    public List<Sensor> getSensorDataByName(String name) {
        return sensorRepository.getSensorDataByName(name);
    }
}
