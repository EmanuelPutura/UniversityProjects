package sdi.web.dto.add;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.ToString;

import java.util.Objects;

@NoArgsConstructor
@AllArgsConstructor
@Data
@ToString(callSuper = true)
public class AddDto {
    private Long movieId;
    private Long actorId;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || AddDto.class != o.getClass()) return false;
        var dto = (AddDto) o;
        return Objects.equals(movieId, dto.getMovieId()) && Objects.equals(actorId, dto.getActorId());
    }
}
