import { Component, OnInit } from '@angular/core';
import {Technician} from "../model/technician";
import {Router} from "@angular/router";
import {TechniciansService} from "../service/technicians.service";

@Component({
  selector: 'app-technicians-list',
  templateUrl: './technicians-list.component.html',
  styleUrls: ['./technicians-list.component.css']
})
export class TechniciansListComponent implements OnInit {
  errorMessage: string;
  technicians: Array<Technician>;
  selectedTechnician: Technician;

  constructor(private techniciansService: TechniciansService, private router: Router) {
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

  onSelect(student: Technician): void {
    this.selectedTechnician = student;
  }

  gotoDetail(): void {
    this.router.navigate(['/technicians/details', this.selectedTechnician.id]);
  }
}
