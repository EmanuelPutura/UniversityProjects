import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {DevicesService} from "../service/devices.service";

@Component({
  selector: 'app-devices-insert',
  templateUrl: './devices-insert.component.html',
  styleUrls: ['./devices-insert.component.css']
})
export class DevicesInsertComponent implements OnInit {
  constructor(private devicesService: DevicesService, private router: Router) {
  }

  ngOnInit(): void {
  }

  saveDevice(type: string, brand: string, model: string, clientId: string) {
    const clientIdNumber: number = Number(clientId);
    if (isNaN(clientIdNumber) || clientIdNumber < 0) {
      alert("Device client ID must be a positive number!");
      return;
    }

    this.devicesService.save({id: 0, type, brand, model, clientId: clientIdNumber})
      .subscribe(_ => this.router.navigate(['/devices']), error => alert("Error: Invalid device data!"));
  }
}
