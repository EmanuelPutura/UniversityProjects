import {Component, Input, OnInit} from '@angular/core';
import {Technician} from "../model/technician";
import {ActivatedRoute, Params} from "@angular/router";
import {Location} from "@angular/common";
import {TechniciansService} from "../service/technicians.service";
import {switchMap} from "rxjs";

@Component({
  selector: 'app-technicians-detail',
  templateUrl: './technicians-detail.component.html',
  styleUrls: ['./technicians-detail.component.css']
})
export class TechniciansDetailComponent implements OnInit {
  @Input() technician: Technician | undefined;

  constructor(private techniciansService: TechniciansService, private route: ActivatedRoute, private location: Location) {
  }

  ngOnInit(): void {
    this.route.params
      .pipe(switchMap((params: Params) => this.techniciansService.getTechnician(+ params['id'])))
      .subscribe(technician => this.technician = technician);
  }

  goBack(): void {
    this.location.back();
  }

  save(): void {
    if (this.technician && !isNaN(Number(this.technician.salary)) && Number(this.technician.salary) >= 0) {
      this.technician.salary = Number(this.technician.salary);
      this.techniciansService.update(this.technician)
        .subscribe(_ => this.goBack());
    }
    else {
      alert("Invalid technician details!");
    }
  }

  delete(): void {
    if (this.technician) {
      this.techniciansService.delete(this.technician).subscribe(_ => this.goBack());
    }
  }
}
