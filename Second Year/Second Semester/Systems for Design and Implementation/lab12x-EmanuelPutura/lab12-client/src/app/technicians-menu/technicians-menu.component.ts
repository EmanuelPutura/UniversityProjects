import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

@Component({
  selector: 'app-technicians-menu',
  templateUrl: './technicians-menu.component.html',
  styleUrls: ['./technicians-menu.component.css']
})
export class TechniciansMenuComponent implements OnInit {

  constructor(private router: Router) { }

  ngOnInit(): void {
  }

  addTechnician(): void {
    this.router.navigate(['/technicians/save']);
  }
}
