import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {map, Observable} from "rxjs";
import {Movie} from "../model/Movie";
import {MovieWithActors} from "../model/MovieWithActors";

@Injectable({
  providedIn: 'root'
})
export class MovieService {
  private moviesUrl = 'http://localhost:8080/movieapp/movies';

  constructor(private httpClient: HttpClient) {
  }

  getMovies(): Observable<Movie[]> {
    return this.httpClient
      .get<any>(this.moviesUrl).pipe(map(result => result.movies));
  }

  getMoviesContainingTitle(title: String): Observable<Movie[]> {
    return this.httpClient
      .get<any>(this.moviesUrl + "/search?title=" + title).pipe(map(result => result.movies));
  }

  getMovieWithActors(id: number): Observable<MovieWithActors> {
    return this.httpClient
      .get<MovieWithActors>(this.moviesUrl + "/searchWithActors?id=" + id.toString());
  }

  addActorToMovie(movieId: number, actorId: number): Observable<MovieWithActors> {
    return this.httpClient.post<MovieWithActors>(this.moviesUrl + "/add", {movieId, actorId});
  }
}
