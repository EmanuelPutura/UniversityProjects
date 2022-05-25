import { Component, OnInit } from '@angular/core';
import {Device} from "../model/device";
import {DevicesService} from "../service/devices.service";
import {Router} from "@angular/router";
import {Client} from "../../clients-menu/model/client";
import {ClientsService} from "../../clients-menu/service/clients.service";

@Component({
  selector: 'app-devices-associated-with-list',
  templateUrl: './devices-associated-with-list.component.html',
  styleUrls: ['./devices-associated-with-list.component.css']
})
export class DevicesAssociatedWithListComponent implements OnInit {
  errorMessage: string;
  devices: Array<Device>;
  clients: Array<Client>;
  selectedClient: Client;

  constructor(private devicesService: DevicesService, private clientsService: ClientsService, private router: Router) {
  }

  ngOnInit(): void {
    this.getClients();
  }

  getClients(): void {
    this.clientsService.getClients()
      .subscribe(
        clients => {
          this.clients = clients
        },
        error => this.errorMessage = <any>error
      );
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
