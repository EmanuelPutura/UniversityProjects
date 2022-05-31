import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {Technician} from "../model/technician";
import {TechniciansService} from "../service/technicians.service";

@Component({
  selector: 'app-technicians-paginated',
  templateUrl: './technicians-paginated.component.html',
  styleUrls: ['./technicians-paginated.component.css']
})
export class TechniciansPaginatedComponent implements OnInit {
  errorMessage: string;
  technicians: Array<Technician>;

  constructor(private techniciansService: TechniciansService, private router: Router) {
  }

  ngOnInit(): void {
  }

  getTechniciansPaginated(page: string, size: string): void {
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

    this.techniciansService.getTechniciansPaginated(pageNumber, sizeNumber)
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
