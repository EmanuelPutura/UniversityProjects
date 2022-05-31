import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

export enum DisplayOption {
  ALL,
  PAGINATED,
  HAVING_CLIENT,
  HAVING_TECHNICIAN
}

@Component({
  selector: 'app-devices-menu',
  templateUrl: './devices-menu.component.html',
  styleUrls: ['./devices-menu.component.css']
})
export class DevicesMenuComponent implements OnInit {
  displayOption: DisplayOption = DisplayOption.ALL;

  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addDevice(): void {
    this.router.navigate(['/devices/save']);
  }

  displayAll(): void {
    this.displayOption = DisplayOption.ALL;
  }

  displayAllPaginated(): void {
    this.displayOption = DisplayOption.PAGINATED;
  }

  displayAllHavingClient(): void {
    this.displayOption = DisplayOption.HAVING_CLIENT;
  }

  displayAllHavingTechnician(): void {
    this.displayOption = DisplayOption.HAVING_TECHNICIAN;
  }
}
