import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

export enum DisplayOption {
  ALL,
  PAGINATED
}

@Component({
  selector: 'app-workshop-teams-menu',
  templateUrl: './workshop-teams-menu.component.html',
  styleUrls: ['./workshop-teams-menu.component.css']
})
export class WorkshopTeamsMenuComponent implements OnInit {
  displayOption: DisplayOption = DisplayOption.ALL;

  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addWorkshopTeam(): void {
    this.router.navigate(['/teams/save']);
  }

  displayAll(): void {
    this.displayOption = DisplayOption.ALL;
  }

  displayAllPaginated(): void {
    this.displayOption = DisplayOption.PAGINATED;
  }
}
