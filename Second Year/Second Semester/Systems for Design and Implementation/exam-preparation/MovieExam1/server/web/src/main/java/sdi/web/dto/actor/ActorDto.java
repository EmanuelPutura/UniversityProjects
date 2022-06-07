package sdi.web.dto.actor;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import sdi.web.dto.BaseDto;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class ActorDto extends BaseDto {
    private String name;
    private Integer rating;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || ActorDto.class != o.getClass()) return false;
        var dto = (ActorDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
