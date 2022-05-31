import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

export enum DisplayOption {
  ALL,
  PAGINATED,
  FILTERED_SORTED
}

@Component({
  selector: 'app-clients-menu',
  templateUrl: './clients-menu.component.html',
  styleUrls: ['./clients-menu.component.css']
})
export class ClientsMenuComponent implements OnInit {
  displayOption: DisplayOption = DisplayOption.ALL;

  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addClient(): void {
    this.router.navigate(['/clients/save']);
  }

  displayAll(): void {
    this.displayOption = DisplayOption.ALL;
  }

  displayAllPaginated(): void {
    this.displayOption = DisplayOption.PAGINATED;
  }

  displayAllHavingClient(): void {
    this.displayOption = DisplayOption.FILTERED_SORTED;
  }
}
