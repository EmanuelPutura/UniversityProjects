import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

@Component({
  selector: 'app-devices-menu',
  templateUrl: './devices-menu.component.html',
  styleUrls: ['./devices-menu.component.css']
})
export class DevicesMenuComponent implements OnInit {
  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addDevice(): void {
    this.router.navigate(['/devices/save']);
  }
}
