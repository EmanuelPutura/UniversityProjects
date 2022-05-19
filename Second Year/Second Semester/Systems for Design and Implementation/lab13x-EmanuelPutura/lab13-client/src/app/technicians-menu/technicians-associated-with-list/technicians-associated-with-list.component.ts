import { Component, OnInit } from '@angular/core';
import {Technician} from "../model/technician";
import {Router} from "@angular/router";
import {TechniciansService} from "../service/technicians.service";

@Component({
  selector: 'app-technicians-associated-with-list',
  templateUrl: './technicians-associated-with-list.component.html',
  styleUrls: ['./technicians-associated-with-list.component.css']
})
export class TechniciansAssociatedWithListComponent implements OnInit {
  errorMessage: string;
  technicians: Array<Technician>;

  constructor(private techniciansService: TechniciansService, private router: Router) {
  }

  ngOnInit(): void {
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
