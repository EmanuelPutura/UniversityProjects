package sdi.core.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import sdi.core.model.Actor;
import sdi.core.model.Movie;
import sdi.core.repository.ActorRepository;
import sdi.core.repository.MovieRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class ActorServiceImpl implements ActorService {
    private final ActorRepository actorRepository;
    private final MovieRepository movieRepository;

    @Autowired
    public ActorServiceImpl(ActorRepository repository, MovieRepository movieRepository) {
        this.actorRepository = repository;
        this.movieRepository = movieRepository;
    }

    @Override
    public List<Actor> getAllActors() {
        return new ArrayList<>(actorRepository.findAll());
    }

    @Override
    public List<Actor> getAllAvailableActors() {
        List<Movie> allMovies = movieRepository.findAllWithActors();
        List<Actor> notAvailableActors = new ArrayList<>();

        allMovies.forEach(movie -> notAvailableActors.addAll(movie.getMovieActors()));
        return actorRepository.findAll().stream().filter(actor -> !notAvailableActors.contains(actor)).collect(Collectors.toList());
    }
}
