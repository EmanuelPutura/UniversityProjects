import { Component, OnInit } from '@angular/core';
import {Technician} from "../model/technician";
import {Router} from "@angular/router";
import {TechniciansService} from "../service/technicians.service";
import {Device} from "../../devices-menu/model/device";
import {DevicesService} from "../../devices-menu/service/devices.service";
import {Client} from "../../clients-menu/model/client";

@Component({
  selector: 'app-technicians-associated-with-list',
  templateUrl: './technicians-associated-with-list.component.html',
  styleUrls: ['./technicians-associated-with-list.component.css']
})
export class TechniciansAssociatedWithListComponent implements OnInit {
  errorMessage: string;
  technicians: Array<Technician>;
  devices: Array<Device>;
  selectedDevice: Device;
  selectedDeviceClient: Client;

  constructor(private techniciansService: TechniciansService, private devicesService: DevicesService, private router: Router) {
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
    this.fetchClientForDeviceData();

    if (this.selectedDevice != null) {
      this.getTechniciansAssociatedWithDevice(this.selectedDevice.id.toString());
    }
  }

  fetchClientForDeviceData(): void {
    this.devicesService.getClientForDevice(this.selectedDevice).subscribe(
      client => {
        this.selectedDeviceClient = client
      },
      error => this.errorMessage = <any>error
    );
  }

  getTechniciansAssociatedWithDevice(deviceId: string): void {
    const deviceIdNumber: number = Number(deviceId);
    if (isNaN(deviceIdNumber) || deviceIdNumber < 0) {
      alert("Device ID must be a positive number!");
      return;
    }

    this.techniciansService.getTechniciansAssociatedWithDevice(deviceIdNumber)
      .subscribe(
        technicians => {
          this.technicians = technicians
        },
        error => {
          this.errorMessage = <any>error;
          alert("Error: Invalid data given!");
        }
      );
  }
}
