import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {map, Observable} from "rxjs";
import {Actor} from "../model/Actor";

@Injectable({
  providedIn: 'root'
})
export class ActorService {
  private actorsUrl = 'http://localhost:8080/movieapp/actors';

  constructor(private httpClient: HttpClient) { }

  getAllAvailableActors(): Observable<Actor[]> {
    return this.httpClient
      .get<any>(this.actorsUrl + "/available").pipe(map(result => result.actors));
  }
}
