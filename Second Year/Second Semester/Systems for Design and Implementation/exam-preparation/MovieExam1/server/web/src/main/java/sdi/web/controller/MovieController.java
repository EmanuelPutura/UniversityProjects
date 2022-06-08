package sdi.web.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import sdi.core.service.MovieService;
import sdi.web.converter.MovieConverter;
import sdi.web.converter.MovieWithActorsConverter;
import sdi.web.dto.add.AddDto;
import sdi.web.dto.movie.MovieDtos;
import sdi.web.dto.movie.MovieWithActorsDto;

import java.util.stream.Collectors;

@RestController
@CrossOrigin(allowedHeaders = "*")
public class MovieController {
    private final MovieService movieService;
    private final MovieConverter movieConverter;
    private final MovieWithActorsConverter movieWithActorsConverter;

    @Autowired
    public MovieController(MovieService movieService, MovieConverter movieConverter, MovieWithActorsConverter movieWithActorsConverter) {
        this.movieService = movieService;
        this.movieConverter = movieConverter;
        this.movieWithActorsConverter = movieWithActorsConverter;
    }

    @RequestMapping(value = "/movies")
    MovieDtos getAllMovies() {
        return new MovieDtos(movieConverter.convertModelsToDtos(movieService.getAllMovies()));
    }

    @RequestMapping(value = "/movies/search")
    MovieDtos getAllMoviesContainingTitle(@RequestParam String title) {
        return new MovieDtos(movieConverter.convertModelsToDtos(movieService.getAllMovies().stream().filter(m -> m.getTitle().contains(title)).collect(Collectors.toList())));
    }

    @RequestMapping(value = "/movies/searchWithActors")
    MovieWithActorsDto getMovieWithActors(@RequestParam Long id) {
        var movie = movieService.getMovieWithActors(id);
        if (movie == null) {
            return null;
        }

        return movieWithActorsConverter.convertModelToDto(movieService.getMovieWithActors(id));
    }

    @RequestMapping(value = "movies/add", method = RequestMethod.POST)
    MovieWithActorsDto addActorToMovie(@RequestBody AddDto addDto) {
        return movieWithActorsConverter.convertModelToDto(movieService.addActor(addDto.getMovieId(), addDto.getActorId()));
    }
}
