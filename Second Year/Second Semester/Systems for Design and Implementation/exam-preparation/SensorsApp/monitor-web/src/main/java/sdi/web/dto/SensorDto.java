package sdi.web.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

import java.time.LocalTime;
import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class SensorDto extends BaseDto {
    private String name;
    private Double measurement;
    private LocalTime time;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || SensorDto.class != o.getClass()) return false;
        SensorDto client = (SensorDto) o;
        return getId() != null && Objects.equals(getId(), client.getId());
    }
}
