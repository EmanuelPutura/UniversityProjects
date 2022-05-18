import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

@Component({
  selector: 'app-devices-menu',
  templateUrl: './devices-menu.component.html',
  styleUrls: ['./devices-menu.component.css']
})
export class DevicesMenuComponent implements OnInit {
  displayFlag: boolean = true; // true when all devices are displayed, false when all devices associated with a client are displayed

  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addDevice(): void {
    this.router.navigate(['/devices/save']);
  }

  displayAll(): void {
    this.displayFlag = true;
  }

  displayAllHavingClient(): void {
    this.displayFlag = false;
  }
}
