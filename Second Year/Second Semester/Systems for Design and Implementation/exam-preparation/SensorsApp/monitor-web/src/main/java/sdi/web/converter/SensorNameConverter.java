package sdi.web.converter;

import org.springframework.stereotype.Component;
import sdi.core.model.Sensor;
import sdi.core.model.SensorNameDto;

import java.util.Collection;
import java.util.Set;
import java.util.stream.Collectors;

@Component
public class SensorNameConverter {
    public SensorNameDto convertModelToDto(Sensor sensor) {
        return (SensorNameDto) new SensorNameDto(sensor.getName());
    }

    public Set<SensorNameDto> convertModelsToDtos(Collection<Sensor> models) {
        return models.stream()
                .map(this::convertModelToDto)
                .collect(Collectors.toSet());
    }
}
