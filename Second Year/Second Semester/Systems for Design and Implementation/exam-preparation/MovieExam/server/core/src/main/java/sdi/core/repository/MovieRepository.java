package sdi.core.repository;

import org.springframework.data.jpa.repository.EntityGraph;
import org.springframework.data.jpa.repository.Query;
import sdi.core.model.Movie;

import java.util.List;

public interface MovieRepository extends MovieAppRepository<Movie, Long> {
    @Query("select distinct m from Movie m")
    @EntityGraph(value = "Movie.movieWithActors", type = EntityGraph.EntityGraphType.LOAD)
    List<Movie> findAllWithActors();
}
