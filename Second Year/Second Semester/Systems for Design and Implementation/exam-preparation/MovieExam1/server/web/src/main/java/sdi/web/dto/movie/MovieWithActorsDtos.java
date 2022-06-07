package sdi.web.dto.movie;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Set;

@NoArgsConstructor
@AllArgsConstructor
@Data
public class MovieWithActorsDtos {
    private Set<MovieWithActorsDto> movies;
}
