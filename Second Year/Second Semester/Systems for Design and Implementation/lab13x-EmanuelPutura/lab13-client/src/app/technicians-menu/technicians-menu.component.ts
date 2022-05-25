import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

export enum DisplayOption {
  ALL,
  PAGINATED,
  HAVING_CLIENT
}

@Component({
  selector: 'app-technicians-menu',
  templateUrl: './technicians-menu.component.html',
  styleUrls: ['./technicians-menu.component.css']
})
export class TechniciansMenuComponent implements OnInit {
  displayOption: DisplayOption = DisplayOption.ALL;

  constructor(private router: Router) { }

  ngOnInit(): void {
  }

  addTechnician(): void {
    this.router.navigate(['/technicians/save']);
  }

  displayAll(): void {
    this.displayOption = DisplayOption.ALL;
  }

  displayAllPaginated(): void {
    this.displayOption = DisplayOption.PAGINATED;
  }

  displayAllHavingDevice(): void {
    this.displayOption = DisplayOption.HAVING_CLIENT;
  }
}
