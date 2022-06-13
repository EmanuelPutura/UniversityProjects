import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {AppComponent} from "./app.component";
import {MovieSearchComponent} from "./movie-search/movie-search.component";
import {MovieDetailsComponent} from "./movie-details/movie-details.component";

const routes: Routes = [
  { path: 'movieapp/movies', component: MovieSearchComponent },
  { path: 'movieapp/movie/details/:id', component: MovieDetailsComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
