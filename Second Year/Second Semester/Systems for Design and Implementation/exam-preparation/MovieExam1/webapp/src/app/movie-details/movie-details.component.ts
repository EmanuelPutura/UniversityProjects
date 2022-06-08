import { Component, OnInit } from '@angular/core';
import {MovieService} from "../service/movie.service";
import {ActivatedRoute, Params} from "@angular/router";
import {switchMap} from "rxjs";
import {MovieWithActors} from "../model/MovieWithActors";
import {ActorService} from "../service/actor.service";
import {Actor} from "../model/Actor";

@Component({
  selector: 'app-movie-details',
  templateUrl: './movie-details.component.html',
  styleUrls: ['./movie-details.component.css']
})
export class MovieDetailsComponent implements OnInit {
  errorMessage: string;
  movie: MovieWithActors;
  selectedActor: Actor;
  availableActors: Actor[];
  addMoreActors: boolean = false;

  constructor(private movieService: MovieService, private actorService: ActorService, private route: ActivatedRoute) { }

  ngOnInit(): void {
    this.route.params
      .pipe(switchMap((params: Params) => this.movieService.getMovieWithActors(+ params['id'])))
      .subscribe(movie => this.movie = movie);
  }

  onAddMoreActorsBtn(): void {
    this.addMoreActors = true;
    this.actorService.getAllAvailableActors().subscribe(
      actors => {
        this.availableActors = actors
      },
      error => this.errorMessage = <any>error
    );
  }

  onAddButton(actor: Actor): void {
    this.movieService.addActorToMovie(this.movie.id, actor.id)
      .subscribe(movie => {
        this.movie = movie;
        this.onAddMoreActorsBtn();
      }, error => alert("Error!"));
  }
}
