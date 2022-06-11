package sdi.server.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import sdi.server.model.Sensor;
import sdi.server.repository.SensorRepository;

@Service
public class SensorServiceImpl {
    private final SensorRepository sensorRepository;

    @Autowired
    public SensorServiceImpl(SensorRepository sensorRepository) {
        this.sensorRepository = sensorRepository;
    }

    public Sensor save(Sensor sensor) {
        return sensorRepository.save(sensor);
    }
}
