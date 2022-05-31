import { Component, OnInit } from '@angular/core';
import {WorkshopTeam} from "../model/workshop-team";
import {Technician} from "../../technicians-menu/model/technician";
import {Router} from "@angular/router";
import {WorkshopTeamsService} from "../service/workshop-teams.service";
import {Device} from "../../devices-menu/model/device";

@Component({
  selector: 'app-workshop-teams-paginated',
  templateUrl: './workshop-teams-paginated.component.html',
  styleUrls: ['./workshop-teams-paginated.component.css']
})
export class WorkshopTeamsPaginatedComponent implements OnInit {
  errorMessage: string;
  teams: Array<WorkshopTeam>;
  selectedWorkshopTeam: WorkshopTeam;
  selectedWorkshopTeamTechnician: Technician;

  constructor(private teamsService: WorkshopTeamsService, private router: Router) {
  }

  ngOnInit(): void {
  }

  getWorkshopTeamPaginated(page: string, size: string): void {
    const pageNumber: number = Number(page);
    if (isNaN(pageNumber) || pageNumber < 0) {
      alert("Page number must be a positive number!");
      return;
    }

    const sizeNumber: number = Number(size);
    if (isNaN(sizeNumber) || sizeNumber < 0) {
      alert("Page size must be a positive number!");
      return;
    }

    this.teamsService.getWorkshopTeamsPaginated(pageNumber, sizeNumber)
      .subscribe(
        teams => {
          this.teams = teams
        },
        error => {
          this.errorMessage = <any>error;
          alert("Error: Invalid data given!");
        }
      );
  }

  onSelect(workshopTeam: WorkshopTeam): void {
    this.selectedWorkshopTeam = workshopTeam;
    this.fetchTechnicianForWorkshopTeamData();
  }

  fetchTechnicianForWorkshopTeamData(): void {
    this.teamsService.getTechnicianForWorkshopTeam(this.selectedWorkshopTeam).subscribe(
      technician => {
        this.selectedWorkshopTeamTechnician = technician
      },
      error => this.errorMessage = <any>error
    );
  }
}
