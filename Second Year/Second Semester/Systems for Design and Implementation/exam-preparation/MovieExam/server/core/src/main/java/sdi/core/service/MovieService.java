package sdi.core.service;

import sdi.core.model.Movie;

import java.util.List;

public interface MovieService {
    List<Movie> getAllMovies();

    Movie getMovieWithActors(Long movieId);

    Movie addActor(Long movieId, Long actorId);
}
