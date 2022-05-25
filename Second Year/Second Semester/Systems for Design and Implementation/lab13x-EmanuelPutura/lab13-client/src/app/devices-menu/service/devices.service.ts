import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";
import {map} from "rxjs/operators";
import {Device} from "../model/device";
import {Client} from "../../clients-menu/model/client";

@Injectable({
  providedIn: 'root'
})
export class DevicesService {
  private baseUrl = 'http://localhost:8080/api/';
  private devicesUrl = this.baseUrl + 'devices';
  private ordersUrl = this.baseUrl + 'orders';

  constructor(private httpClient: HttpClient) {
  }

  getDevices(): Observable<Device[]> {
    return this.httpClient.get<any>(this.devicesUrl).pipe(map(result => result.devices));
  }

  getDevicesPaginated(pageNumber: number, pageSize: number): Observable<Device[]> {
    const requestUrl = this.devicesUrl + "/paginated?page=" + pageNumber.toString() + "&size=" + pageSize.toString();
    return this.httpClient.get<any>(requestUrl).pipe(map(result => result.devices));
  }

  getDevicesAssociatedWithClient(clientId: number): Observable<Device[]> {
    return this.httpClient.get<any>(this.devicesUrl + "/forClient?deviceId=" + clientId.toString()).pipe(map(result => result.devices));
  }

  getDevicesAssociatedWithTechnician(technicianId: number): Observable<Device[]> {
    return this.httpClient.get<any>(this.ordersUrl + "/forTechnician?technicianId=" + technicianId.toString()).pipe(map(result => result.devices));
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

  getClientForDevice(device: Device): Observable<Client> {
    const url = this.baseUrl + "clients/findById?clientId=" + device.clientId;
    return this.httpClient.get<Client>(url);
  }
}
