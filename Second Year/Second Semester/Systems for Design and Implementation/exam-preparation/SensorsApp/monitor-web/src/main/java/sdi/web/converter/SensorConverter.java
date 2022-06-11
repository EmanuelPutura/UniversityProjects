package sdi.web.converter;

import org.springframework.stereotype.Component;
import sdi.core.model.Sensor;
import sdi.web.dto.BaseDto;
import sdi.web.dto.SensorDto;

@Component
public class SensorConverter extends BaseConverter<Sensor, SensorDto>{

    @Override
    public Sensor convertDtoToModel(SensorDto dto) {
        var model = new Sensor();

        model.setId(dto.getId());
        model.setName(dto.getName());
        model.setMeasurement(dto.getMeasurement());
        model.setTime(dto.getTime());

        return model;
    }

    @Override
    public SensorDto convertModelToDto(Sensor sensor) {
        SensorDto dto = new SensorDto(sensor.getName(), sensor.getMeasurement(), sensor.getTime());
        dto.setId(sensor.getId());
        return dto;
    }
}
