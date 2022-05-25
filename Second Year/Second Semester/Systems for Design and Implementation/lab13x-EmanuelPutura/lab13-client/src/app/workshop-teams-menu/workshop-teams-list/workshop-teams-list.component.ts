import { Component, OnInit } from '@angular/core';
import {Client} from "../../clients-menu/model/client";
import {Router} from "@angular/router";
import {WorkshopTeam} from "../model/workshop-team";
import {WorkshopTeamsService} from "../service/workshop-teams.service";
import {Technician} from "../../technicians-menu/model/technician";

@Component({
  selector: 'app-workshop-teams-list',
  templateUrl: './workshop-teams-list.component.html',
  styleUrls: ['./workshop-teams-list.component.css']
})
export class WorkshopTeamsListComponent implements OnInit {
  errorMessage: string;
  teams: Array<WorkshopTeam>;
  selectedWorkshopTeam: WorkshopTeam;
  selectedWorkshopTeamTechnician: Technician;

  constructor(private teamsService: WorkshopTeamsService, private router: Router) {
  }

  ngOnInit(): void {
    this.getWorkshopTeams();
  }

  getWorkshopTeams(): void {
    this.teamsService.getWorkshopTeams()
      .subscribe(
        teams => {
          this.teams = teams
        },
        error => this.errorMessage = <any>error
      );
  }

  onSelect(team: WorkshopTeam): void {
    this.selectedWorkshopTeam = team;
    this.fetchTechnicianForWorkshopTeamData();
  }

  gotoDetail(): void {
    this.router.navigate(['/teams/details', this.selectedWorkshopTeam.id]);
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
