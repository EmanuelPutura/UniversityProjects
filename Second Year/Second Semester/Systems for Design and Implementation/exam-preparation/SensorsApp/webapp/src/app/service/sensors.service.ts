import { Injectable } from '@angular/core';
import {Sensor} from "../model/sensor";
import {map, Observable} from "rxjs";
import {HttpClient} from "@angular/common/http";

@Injectable({
  providedIn: 'root'
})
export class SensorsService {
  private baseUrl = 'http://localhost:8080/sensors';

  constructor(private httpClient: HttpClient) { }

  getSensors(): Observable<Sensor[]> {
    const url = `${this.baseUrl}/sensor1`;
    return this.httpClient.get<any>(url).pipe(map(result => result.sensors));
  }
}
