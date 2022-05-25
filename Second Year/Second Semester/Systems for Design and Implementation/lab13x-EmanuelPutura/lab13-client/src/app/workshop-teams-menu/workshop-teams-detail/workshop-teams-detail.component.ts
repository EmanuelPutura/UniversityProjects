import {Component, Input, OnInit} from '@angular/core';
import {ActivatedRoute, Params} from "@angular/router";
import {Location} from "@angular/common";
import {switchMap} from "rxjs";
import {WorkshopTeam} from "../model/workshop-team";
import {WorkshopTeamsService} from "../service/workshop-teams.service";
import {Technician} from "../../technicians-menu/model/technician";
import {TechniciansService} from "../../technicians-menu/service/technicians.service";

@Component({
  selector: 'app-workshop-teams-detail',
  templateUrl: './workshop-teams-detail.component.html',
  styleUrls: ['./workshop-teams-detail.component.css']
})
export class WorkshopTeamsDetailComponent implements OnInit {
  @Input() team: WorkshopTeam | undefined;
  errorMessage: string;

  technicians: Array<Technician>;
  selectedTechnician: Technician;

  initialTechnician: Technician

  constructor(private techniciansService: TechniciansService, private teamsService: WorkshopTeamsService, private route: ActivatedRoute, private location: Location) {
  }

  ngOnInit(): void {
    this.getTechnicians();

    this.route.params
      .pipe(switchMap((params: Params) => this.teamsService.getWorkshopTeam(+params['id'])))
      .subscribe(team => {
        this.team = team;
        if (this.team != undefined) {
          this.teamsService.getTechnicianForWorkshopTeam(this.team).subscribe(technician => this.initialTechnician = technician);
        }
      });
  }

  goBack(): void {
    this.location.back();
  }

  save(): void {
    if (this.team) {
      this.teamsService.update(this.team)
        .subscribe(_ => this.goBack(), error => alert("Error: Invalid team details!"));
    } else {
      alert("Invalid team details!");
    }
  }

  delete(): void {
    if (this.team) {
      this.teamsService.delete(this.team).subscribe(_ => this.goBack());
    }
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
}
