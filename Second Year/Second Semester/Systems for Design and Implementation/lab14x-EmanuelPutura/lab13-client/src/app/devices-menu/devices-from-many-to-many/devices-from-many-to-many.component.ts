import { Component, OnInit } from '@angular/core';
import {Technician} from "../../technicians-menu/model/technician";
import {Device} from "../model/device";
import {Client} from "../../clients-menu/model/client";
import {TechniciansService} from "../../technicians-menu/service/technicians.service";
import {DevicesService} from "../service/devices.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-devices-from-many-to-many',
  templateUrl: './devices-from-many-to-many.component.html',
  styleUrls: ['./devices-from-many-to-many.component.css']
})
export class DevicesFromManyToManyComponent implements OnInit {
  errorMessage: string;
  technicians: Array<Technician>;
  selectedTechnician: Technician;
  devices: Array<Device>;
  selectedDevice: Device;
  selectedDeviceClient: Client;

  constructor(private techniciansService: TechniciansService, private devicesService: DevicesService, private router: Router) {
  }

  ngOnInit(): void {
    this.getTechnicians();
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

  onSelectDevice(device: Device): void {
    this.selectedDevice = device;
    this.fetchClientForDeviceData();
  }

  onSelectTechnician(technician: Technician): void {
    this.selectedTechnician = technician;

    if (this.selectedTechnician != null) {
      this.getDevicesAssociatedWithTechnician(this.selectedTechnician.id.toString());
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

  getDevicesAssociatedWithTechnician(technicianId: string): void {
    const technicianIdNumber: number = Number(technicianId);
    if (isNaN(technicianIdNumber) || technicianIdNumber < 0) {
      alert("Technician ID must be a positive number!");
      return;
    }

    this.devicesService.getDevicesAssociatedWithTechnician(technicianIdNumber)
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
