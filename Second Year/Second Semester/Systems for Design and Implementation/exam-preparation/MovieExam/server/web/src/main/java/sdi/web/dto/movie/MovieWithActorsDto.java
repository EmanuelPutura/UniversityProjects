package sdi.web.dto.movie;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;
import sdi.web.dto.BaseDto;
import sdi.web.dto.actor.ActorDto;

import java.util.Objects;
import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class MovieWithActorsDto extends BaseDto {
    private String title;
    private Integer year;
    private Set<ActorDto> actors;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || MovieDto.class != o.getClass()) return false;
        var dto = (MovieDto) o;
        return getId() != null && Objects.equals(getId(), dto.getId());
    }
}
