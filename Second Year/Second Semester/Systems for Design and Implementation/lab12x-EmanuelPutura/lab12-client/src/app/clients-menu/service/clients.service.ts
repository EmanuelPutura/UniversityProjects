import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";
import {Client} from "../model/client";
import {map} from "rxjs/operators";

@Injectable({
  providedIn: 'root'
})
export class ClientsService {
  private clientsUrl = 'http://localhost:8080/api/clients';

  constructor(private httpClient: HttpClient) {
  }

  getClients(): Observable<Client[]> {
    return this.httpClient
      .get<any>(this.clientsUrl).pipe(map(result => result.clients));
  }

  getClient(id: number): Observable<Client | undefined> {
    return this.getClients().pipe(
      map(clients => clients.find(client => client.id === id))
    );
  }

  save(client: Client): Observable<Client> {
    return this.httpClient.post<Client>(this.clientsUrl, client);
  }

  update(client: Client): Observable<Client> {
    const url = `${this.clientsUrl}/${client.id}`;
    return this.httpClient.put<Client>(url, client);
  }

  delete(client: Client): Observable<Object> {
    const url = `${this.clientsUrl}/${client.id}`;
    return this.httpClient.delete(url);
  }
}
