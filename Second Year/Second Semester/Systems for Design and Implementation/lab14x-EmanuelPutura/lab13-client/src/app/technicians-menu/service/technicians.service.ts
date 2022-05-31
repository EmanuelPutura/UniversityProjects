import { Injectable } from '@angular/core';
import {Observable} from "rxjs";
import {map} from "rxjs/operators";
import {HttpClient} from "@angular/common/http";
import {Technician} from "../model/technician";

@Injectable({
  providedIn: 'root'
})
export class TechniciansService {
  private techniciansUrl = 'http://localhost:8080/api/technicians';
  private ordersUrl = 'http://localhost:8080/api/orders';

  constructor(private httpClient: HttpClient) {
  }

  getTechnicians(): Observable<Technician[]> {
    return this.httpClient.get<any>(this.techniciansUrl).pipe(map(result => result.technicians));
  }

  getTechniciansPaginated(pageNumber: number, pageSize: number): Observable<Technician[]> {
    const requestUrl = this.techniciansUrl + "/paginated?page=" + pageNumber.toString() + "&size=" + pageSize.toString();
    return this.httpClient.get<any>(requestUrl).pipe(map(result => result.technicians));
  }

  getTechniciansAssociatedWithDevice(deviceId: number): Observable<Technician[]> {
    return this.httpClient.get<any>(this.ordersUrl + "/forDevice?deviceId=" + deviceId.toString()).pipe(map(result => result.technicians));
  }

  getTechnician(id: number): Observable<Technician | undefined> {
    return this.getTechnicians().pipe(
      map(technicians => technicians.find(technician => technician.id === id))
    );
  }

  save(technician: Technician): Observable<Technician> {
    return this.httpClient.post<Technician>(this.techniciansUrl, technician);
  }

  update(technician: Technician): Observable<Technician> {
    const url = `${this.techniciansUrl}/${technician.id}`;
    return this.httpClient.put<Technician>(url, technician);
  }

  delete(technician: Technician): Observable<Object> {
    const url = `${this.techniciansUrl}/${technician.id}`;
    return this.httpClient.delete(url);
  }
}
