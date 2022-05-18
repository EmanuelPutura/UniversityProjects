import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {TechniciansService} from "../service/technicians.service";

@Component({
  selector: 'app-technicians-insert',
  templateUrl: './technicians-insert.component.html',
  styleUrls: ['./technicians-insert.component.css']
})
export class TechniciansInsertComponent implements OnInit {
  constructor(private techniciansService: TechniciansService, private router: Router) {
  }

  ngOnInit(): void {
  }

  saveTechnician(firstName: string, lastName: string, salary: string) {
    const salaryNumber: number = Number(salary);
    if (isNaN(salaryNumber) || salaryNumber < 0) {
      alert("Technician salary must be a positive number!");
      return;
    }

    this.techniciansService.save({id: 0, firstName, lastName, salary: salaryNumber})
      .subscribe(_ => this.router.navigate(['/technicians']));
  }
}
