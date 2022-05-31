import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {Technician} from "../../technicians-menu/model/technician";
import {TechniciansService} from "../../technicians-menu/service/technicians.service";
import {WorkshopTeam} from "../model/workshop-team";
import {WorkshopTeamsService} from "../service/workshop-teams.service";

@Component({
  selector: 'app-workshop-teams-insert',
  templateUrl: './workshop-teams-insert.component.html',
  styleUrls: ['./workshop-teams-insert.component.css']
})
export class WorkshopTeamsInsertComponent implements OnInit {
  errorMessage: string;
  technicians: Array<Technician>;
  selectedTechnician: Technician;

  constructor(private techniciansService: TechniciansService, private workshopTeamsService: WorkshopTeamsService, private router: Router) {
  }

  ngOnInit(): void {
    this.getTechnicians();
  }

  getTechnicians(): void {
    this.techniciansService.getTechnicians()
      .subscribe(
        technicians => {
          this.technicians = technicians
        },
        error => this.errorMessage = <any>error
      );
  }

  saveWorkshopTeam(teamName: string) {
    if (this.selectedTechnician == null) {
      alert("Invalid selected technician!");
      return;
    }

    this.workshopTeamsService.save({id: 0, teamName, technicianId: this.selectedTechnician.id})
      .subscribe(_ => this.router.navigate(['/teams']), error => alert("Error: Invalid workshop team data!"));
  }
}
