import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {DevicesService} from "../service/devices.service";
import {ClientsService} from "../../clients-menu/service/clients.service";
import {Client} from "../../clients-menu/model/client";

@Component({
  selector: 'app-devices-insert',
  templateUrl: './devices-insert.component.html',
  styleUrls: ['./devices-insert.component.css']
})
export class DevicesInsertComponent implements OnInit {
  errorMessage: string;
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

  saveDevice(type: string, brand: string, model: string) {
    if (this.selectedClient == null) {
      alert("Invalid selected client!");
      return;
    }

    this.devicesService.save({id: 0, type, brand, model, clientId: this.selectedClient.id})
      .subscribe(_ => this.router.navigate(['/devices']), error => alert("Error: Invalid device data!"));
  }
}
