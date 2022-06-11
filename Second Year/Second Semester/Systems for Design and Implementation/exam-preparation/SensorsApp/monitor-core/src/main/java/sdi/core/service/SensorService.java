package sdi.core.service;

import sdi.core.model.Sensor;
import sdi.core.model.SensorNameDto;

import java.util.List;

public interface SensorService {
    List<Sensor> findAll();

    List<SensorNameDto> getAllSensorNames();

    List<Sensor> getSensorDataByName(String name);
}
