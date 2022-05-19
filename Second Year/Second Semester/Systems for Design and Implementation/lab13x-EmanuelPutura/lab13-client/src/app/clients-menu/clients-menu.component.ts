import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

@Component({
  selector: 'app-clients-menu',
  templateUrl: './clients-menu.component.html',
  styleUrls: ['./clients-menu.component.css']
})
export class ClientsMenuComponent implements OnInit {
  displayFlag: boolean = true;

  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addClient(): void {
    this.router.navigate(['/clients/save']);
  }

  displayAll(): void {
    this.displayFlag = true;
  }

  displayAllHavingClient(): void {
    this.displayFlag = false;
  }
}
