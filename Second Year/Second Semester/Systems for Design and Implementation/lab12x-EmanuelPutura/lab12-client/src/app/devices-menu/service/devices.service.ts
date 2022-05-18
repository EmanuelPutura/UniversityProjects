import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";
import {map} from "rxjs/operators";
import {Device} from "../model/device";

@Injectable({
  providedIn: 'root'
})
export class DevicesService {
  private devicesUrl = 'http://localhost:8080/api/devices';

  constructor(private httpClient: HttpClient) {
  }

  getDevices(): Observable<Device[]> {
    return this.httpClient.get<any>(this.devicesUrl).pipe(map(result => result.devices));
  }

  getDevice(id: number): Observable<Device | undefined> {
    return this.getDevices().pipe(map(devices => devices.find(device => device.id === id)));
  }

  save(device: Device): Observable<Device> {
    return this.httpClient.post<Device>(this.devicesUrl, device);
  }

  update(device: Device): Observable<Device> {
    const url = `${this.devicesUrl}/${device.id}`;
    return this.httpClient.put<Device>(url, device);
  }

  delete(device: Device): Observable<Object> {
    const url = `${this.devicesUrl}/${device.id}`;
    return this.httpClient.delete(url);
  }
}
