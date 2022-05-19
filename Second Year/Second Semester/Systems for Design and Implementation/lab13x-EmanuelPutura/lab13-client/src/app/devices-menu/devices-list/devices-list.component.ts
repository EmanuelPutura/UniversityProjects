import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {Device} from "../model/device";
import {DevicesService} from "../service/devices.service";

@Component({
  selector: 'app-devices-list',
  templateUrl: './devices-list.component.html',
  styleUrls: ['./devices-list.component.css']
})
export class DevicesListComponent implements OnInit {
  errorMessage: string;
  devices: Array<Device>;
  selectedDevice: Device;

  constructor(private devicesService: DevicesService, private router: Router) {
  }

  ngOnInit(): void {
    this.getDevices();
  }

  getDevices(): void {
    this.devicesService.getDevices()
      .subscribe(
        devices => {
          this.devices = devices
        },
        error => this.errorMessage = <any>error
      );
  }

  onSelect(device: Device): void {
    this.selectedDevice = device;
  }

  gotoDetail(): void {
    this.router.navigate(['/devices/details', this.selectedDevice.id]);
  }
}
