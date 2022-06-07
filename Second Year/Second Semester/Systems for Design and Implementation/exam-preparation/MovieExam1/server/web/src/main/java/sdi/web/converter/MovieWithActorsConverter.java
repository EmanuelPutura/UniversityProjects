package sdi.web.converter;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import sdi.core.model.Movie;
import sdi.web.dto.actor.ActorDtos;
import sdi.web.dto.movie.MovieWithActorsDto;

@Component
public class MovieWithActorsConverter extends BaseConverter<Movie, MovieWithActorsDto> {
    private final ActorConverter actorConverter;

    @Autowired
    public MovieWithActorsConverter(ActorConverter actorConverter) {
        this.actorConverter = actorConverter;
    }

    @Override
    public Movie convertDtoToModel(MovieWithActorsDto dto) {
        var model = new Movie();

        model.setId(dto.getId());
        model.setTitle(dto.getTitle());
        model.setYear(dto.getYear());
        model.setMovieActors(actorConverter.convertDtosToModels(dto.getActors().getActors()));

        return model;
    }

    @Override
    public MovieWithActorsDto convertModelToDto(Movie movie) {
        var dto = new MovieWithActorsDto(movie.getTitle(), movie.getYear(), new ActorDtos(actorConverter.convertModelsToDtos(movie.getMovieActors())));
        dto.setId(movie.getId());
        return dto;
    }
}
