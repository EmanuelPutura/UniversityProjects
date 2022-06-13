package sdi.core.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import sdi.core.model.Movie;
import sdi.core.repository.ActorRepository;
import sdi.core.repository.MovieRepository;

import java.util.ArrayList;
import java.util.List;

@Service
public class MovieServiceImpl implements MovieService {
    private final MovieRepository movieRepository;
    private final ActorRepository actorRepository;

    @Autowired
    public MovieServiceImpl(MovieRepository repository, ActorRepository actorRepository) {
        this.movieRepository = repository;
        this.actorRepository = actorRepository;
    }

    @Override
    public List<Movie> getAllMovies() {
        return new ArrayList<>(movieRepository.findAll());
    }

    @Override
    public Movie getMovieWithActors(Long movieId) {
        var movieOptional = movieRepository.findAllWithActors().stream().filter(movie -> movie.getId().equals(movieId)).findFirst();
        if (movieOptional.isEmpty()) {
            return null;
        }

        return movieOptional.get();
    }

    @Override
    @Transactional
    public Movie addActor(Long movieId, Long actorId) {
        var movie = getMovieWithActors(movieId);
        if (movie == null) {
            return null;
        }

        var actor = actorRepository.findActorById(actorId);
        if (actor == null) {
            return null;
        }

        movie.getMovieActors().add(actor);
        return movie;
    }
}
