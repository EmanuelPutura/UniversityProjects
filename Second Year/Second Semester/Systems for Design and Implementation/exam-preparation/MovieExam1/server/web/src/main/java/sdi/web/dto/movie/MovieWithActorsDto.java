package sdi.web.dto.movie;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import sdi.web.dto.BaseDto;
import sdi.web.dto.actor.ActorDtos;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class MovieWithActorsDto extends BaseDto {
    private String title;
    private Integer year;
    private ActorDtos actors;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || MovieDto.class != o.getClass()) return false;
        var dto = (MovieDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
