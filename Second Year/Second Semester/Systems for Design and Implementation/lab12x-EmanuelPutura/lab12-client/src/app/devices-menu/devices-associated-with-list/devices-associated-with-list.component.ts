import { Component, OnInit } from '@angular/core';
import {Device} from "../model/device";
import {DevicesService} from "../service/devices.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-devices-associated-with-list',
  templateUrl: './devices-associated-with-list.component.html',
  styleUrls: ['./devices-associated-with-list.component.css']
})
export class DevicesAssociatedWithListComponent implements OnInit {
  errorMessage: string;
  devices: Array<Device>;

  constructor(private devicesService: DevicesService, private router: Router) {
  }

  ngOnInit(): void {
  }

  getDevicesAssociatedWithClient(clientId: string): void {
    const clientIdNumber: number = Number(clientId);
    if (isNaN(clientIdNumber) || clientIdNumber < 0) {
      alert("Device client ID must be a positive number!");
      return;
    }

    this.devicesService.getDevicesAssociatedWithClient(clientIdNumber)
      .subscribe(
        devices => {
          this.devices = devices
        },
        error => {
          this.errorMessage = <any>error;
          alert("Error: Invalid data given!");
        }
      );
  }
}
