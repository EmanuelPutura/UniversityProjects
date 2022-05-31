import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {Device} from "../model/device";
import {DevicesService} from "../service/devices.service";
import {Client} from "../../clients-menu/model/client";

@Component({
  selector: 'app-devices-paginated',
  templateUrl: './devices-paginated.component.html',
  styleUrls: ['./devices-paginated.component.css']
})
export class DevicesPaginatedComponent implements OnInit {
  errorMessage: string;
  devices: Array<Device>;
  selectedDevice: Device;
  selectedDeviceClient: Client;

  constructor(private devicesService: DevicesService, private router: Router) {
  }

  ngOnInit(): void {
  }

  getDevicesPaginated(page: string, size: string): void {
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

    this.devicesService.getDevicesPaginated(pageNumber, sizeNumber)
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

  onSelect(device: Device): void {
    this.selectedDevice = device;
    this.fetchClientForDeviceData();
  }

  fetchClientForDeviceData(): void {
    this.devicesService.getClientForDevice(this.selectedDevice).subscribe(
      client => {
        this.selectedDeviceClient = client
      },
      error => this.errorMessage = <any>error
    );
  }
}
