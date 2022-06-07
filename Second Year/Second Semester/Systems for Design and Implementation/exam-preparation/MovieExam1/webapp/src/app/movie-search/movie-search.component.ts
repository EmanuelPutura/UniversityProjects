import { Component, OnInit } from '@angular/core';
import {Movie} from "../model/Movie";
import {MovieService} from "../service/movie.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-movie-search',
  templateUrl: './movie-search.component.html',
  styleUrls: ['./movie-search.component.css']
})
export class MovieSearchComponent implements OnInit {
  errorMessage: string;
  movies: Array<Movie>;
  selectedMovie: Movie;
  showMovies: boolean = false;

  constructor(private movieService: MovieService, private router: Router) { }

  ngOnInit(): void {
  }

  onSearchClicked(title: String): void {
    this.showMovies = true;
    this.movieService.getMoviesContainingTitle(title).subscribe(
      movies => {
        this.movies = movies
      },
      error => this.errorMessage = <any>error
    );
  }

  onSelect(movie: Movie): void {
    this.selectedMovie = movie;
    this.router.navigate(['/movieapp/movie/details', this.selectedMovie.id]);
  }
}
