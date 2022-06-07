package sdi.web.converter;

import org.springframework.stereotype.Component;
import sdi.core.model.Movie;
import sdi.web.dto.movie.MovieDto;

@Component
public class MovieConverter extends BaseConverter<Movie, MovieDto> {
    @Override
    public Movie convertDtoToModel(MovieDto dto) {
        var model = new Movie();

        model.setId(dto.getId());
        model.setTitle(dto.getTitle());
        model.setYear(dto.getYear());

        return model;
    }

    @Override
    public MovieDto convertModelToDto(Movie movie) {
        var dto = new MovieDto(movie.getTitle(), movie.getYear());
        dto.setId(movie.getId());
        return dto;
    }
}
