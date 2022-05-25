import {Component, Input, OnInit} from '@angular/core';
import {ActivatedRoute, Params} from "@angular/router";
import {Location} from "@angular/common";
import {switchMap} from "rxjs";
import {Device} from "../model/device";
import {DevicesService} from "../service/devices.service";
import {Technician} from "../../technicians-menu/model/technician";
import {Client} from "../../clients-menu/model/client";
import {ClientsService} from "../../clients-menu/service/clients.service";

@Component({
  selector: 'app-devices-detail',
  templateUrl: './devices-detail.component.html',
  styleUrls: ['./devices-detail.component.css']
})
export class DevicesDetailComponent implements OnInit {
  @Input() device: Device | undefined;
  errorMessage: string;

  clients: Array<Client>;
  selectedClient: Client;
  initialClient: Client

  constructor(private clientsService: ClientsService, private devicesService: DevicesService, private route: ActivatedRoute, private location: Location) {
  }

  ngOnInit(): void {
    this.getClients();

    this.route.params
      .pipe(switchMap((params: Params) => this.devicesService.getDevice(+params['id'])))
      .subscribe(device => {
        this.device = device
        if (this.device != undefined) {
          this.devicesService.getClientForDevice(this.device).subscribe(client => this.initialClient = client);
        }
      });
  }

  goBack(): void {
    this.location.back();
  }

  save(): void {
    if (this.device) {
      this.devicesService.update(this.device)
        .subscribe(_ => this.goBack(), error => alert("Error: Invalid device details!"));
    } else {
      alert("Invalid device details!");
    }
  }

  delete(): void {
    if (this.device) {
      this.devicesService.delete(this.device).subscribe(_ => this.goBack());
    }
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
}
