package sdi.sensors.service;

import sdi.sensors.exceptions.ConnectionException;
import sdi.sensors.domain.Sensor;

import java.util.List;
import java.util.Optional;
import java.util.concurrent.Future;

public interface SensorService {
    Future<List<Sensor>> findAll() throws ConnectionException;
    Future<String> save(Sensor entity) throws ConnectionException;

    Future<Optional<Sensor>> findByName(String name) throws ConnectionException;
}
