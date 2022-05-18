import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";
import {map} from "rxjs/operators";
import {RepairOrder} from "../model/repair-order";

@Injectable({
  providedIn: 'root'
})
export class RepairOrdersService {
  private ordersUrl = 'http://localhost:8080/api/orders';

  constructor(private httpClient: HttpClient) {
  }

  getOrders(): Observable<RepairOrder[]> {
    return this.httpClient.get<any>(this.ordersUrl).pipe(map(result => result.orders));
  }

  getOrder(technicianId: number, deviceId: number): Observable<RepairOrder | undefined> {
    return this.getOrders().pipe(
      map(orders => orders.find(order => order.technicianId === technicianId && order.deviceId === deviceId))
    );
  }

  save(order: RepairOrder): Observable<RepairOrder> {
    return this.httpClient.post<RepairOrder>(this.ordersUrl, order);
  }

  update(order: RepairOrder): Observable<RepairOrder> {
    const url = `${this.ordersUrl}/${order.technicianId}/${order.deviceId}`;
    return this.httpClient.put<RepairOrder>(url, order);
  }

  delete(order: RepairOrder): Observable<Object> {
    const url = `${this.ordersUrl}/${order.technicianId}/${order.deviceId}`;
    return this.httpClient.delete(url);
  }
}
