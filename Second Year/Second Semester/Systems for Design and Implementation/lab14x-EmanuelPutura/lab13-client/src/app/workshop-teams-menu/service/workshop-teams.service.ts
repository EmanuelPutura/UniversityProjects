import { Injectable } from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Observable} from "rxjs";
import {Device} from "../../devices-menu/model/device";
import {map} from "rxjs/operators";
import {Client} from "../../clients-menu/model/client";
import {WorkshopTeam} from "../model/workshop-team";
import {Technician} from "../../technicians-menu/model/technician";

@Injectable({
  providedIn: 'root'
})
export class WorkshopTeamsService {
  private baseUrl = 'http://localhost:8080/api/';
  private workshopTeamsUrl = this.baseUrl + 'teams';

  constructor(private httpClient: HttpClient) {
  }

  getWorkshopTeams(): Observable<WorkshopTeam[]> {
    return this.httpClient.get<any>(this.workshopTeamsUrl).pipe(map(result => result.teams));
  }

  getWorkshopTeamsPaginated(pageNumber: number, pageSize: number): Observable<WorkshopTeam[]> {
    const requestUrl = this.workshopTeamsUrl + "/paginated?page=" + pageNumber.toString() + "&size=" + pageSize.toString();
    return this.httpClient.get<any>(requestUrl).pipe(map(result => result.teams));
  }

  getWorkshopTeam(id: number): Observable<WorkshopTeam | undefined> {
    return this.getWorkshopTeams().pipe(map(teams => teams.find(team => team.id === id)));
  }

  save(workshopTeam: WorkshopTeam): Observable<WorkshopTeam> {
    return this.httpClient.post<WorkshopTeam>(this.workshopTeamsUrl, workshopTeam);
  }

  update(workshopTeam: WorkshopTeam): Observable<WorkshopTeam> {
    const url = `${this.workshopTeamsUrl}/${workshopTeam.id}`;
    return this.httpClient.put<WorkshopTeam>(url, workshopTeam);
  }

  delete(workshopTeam: WorkshopTeam): Observable<Object> {
    const url = `${this.workshopTeamsUrl}/${workshopTeam.id}`;
    return this.httpClient.delete(url);
  }

  getTechnicianForWorkshopTeam(workshopTeam: WorkshopTeam): Observable<Technician> {
    const url = this.baseUrl + "technicians/findById?technicianId=" + workshopTeam.technicianId;
    return this.httpClient.get<Technician>(url);
  }
}
