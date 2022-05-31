import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {Device} from "../devices-menu/model/device";
import {Client} from "../clients-menu/model/client";
import {DevicesService} from "../devices-menu/service/devices.service";
import {Technician} from "../technicians-menu/model/technician";
import {TechniciansService} from "../technicians-menu/service/technicians.service";
import {RepairOrdersService} from "./service/repair-orders.service";

@Component({
  selector: 'app-repair-orders-menu',
  templateUrl: './repair-orders-menu.component.html',
  styleUrls: ['./repair-orders-menu.component.css']
})
export class RepairOrdersMenuComponent implements OnInit {
  errorMessage: string;

  devices: Array<Device>;
  selectedDevice: Device;
  selectedDeviceClient: Client;

  technicians: Array<Technician>;
  selectedTechnician: Technician;

  constructor(private ordersService: RepairOrdersService, private techniciansService: TechniciansService,
              private devicesService: DevicesService, private router: Router) {
  }

  ngOnInit(): void {
    this.getDevices();
    this.getTechnicians();
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

  onSelectDevice(device: Device): void {
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

  getTechnicians(): void {
    this.techniciansService.getTechnicians()
      .subscribe(
        technicians => {
          this.technicians = technicians
        },
        error => this.errorMessage = <any>error
      );
  }

  onSelectTechnician(technician: Technician): void {
    this.selectedTechnician = technician;
  }

  save(): void {
    if (this.selectedDevice == null || this.selectedTechnician == null) {
      alert("No device or no technician was selected!");
      return;
    }

    this.ordersService.save({technicianId: this.selectedTechnician.id, deviceId: this.selectedDevice.id})
      .subscribe(_ => _, error => alert("Error: Invalid order data!"));
  }

  delete(): void {
    if (this.selectedDevice == null || this.selectedTechnician == null) {
      alert("No device or no technician was selected!");
      return;
    }

    this.ordersService.delete({technicianId: this.selectedTechnician.id, deviceId: this.selectedDevice.id})
      .subscribe(_ => _, error => alert("Error: Invalid order data!"));
  }
}
