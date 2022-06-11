package sdi.web.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import sdi.core.model.SensorNameDtos;
import sdi.core.service.SensorService;
import sdi.web.converter.SensorConverter;
import sdi.web.converter.SensorNameConverter;
import sdi.web.dto.SensorDto;
import sdi.web.dto.SensorDtos;

@RestController
@CrossOrigin
public class SensorController {
    private final SensorService sensorService;
    private final SensorConverter sensorConverter;
    private final SensorNameConverter sensorNameConverter;

    @Autowired
    public SensorController(SensorService sensorService, SensorConverter sensorConverter, SensorNameConverter sensorNameConverter) {
        this.sensorService = sensorService;
        this.sensorConverter = sensorConverter;
        this.sensorNameConverter = sensorNameConverter;
    }

    @RequestMapping("/")
    String sayHello() {
        return "Hello world!";
    }

    @RequestMapping("/all")
    SensorDtos fetchAllSensorData() {
        return new SensorDtos(sensorConverter.convertModelsToDtos(sensorService.findAll()));
    }

    @RequestMapping("/sensors")
    SensorNameDtos fetchAllSensorNames() {
        return new SensorNameDtos(sensorNameConverter.convertModelsToDtos(sensorService.findAll()));
    }

    @RequestMapping("/sensors/{name}")
    SensorDtos fetchSensorDataByTime(@PathVariable String name) {
        return new SensorDtos(sensorConverter.convertModelsToDtos(sensorService.getSensorDataByName(name)));
    }
}
