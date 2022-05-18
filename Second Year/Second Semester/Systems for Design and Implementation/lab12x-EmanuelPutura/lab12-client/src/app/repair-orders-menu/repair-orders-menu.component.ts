import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";

@Component({
  selector: 'app-repair-orders-menu',
  templateUrl: './repair-orders-menu.component.html',
  styleUrls: ['./repair-orders-menu.component.css']
})
export class RepairOrdersMenuComponent implements OnInit {
  constructor(private router: Router) {
  }

  ngOnInit(): void {
  }

  addOrder(): void {
    this.router.navigate(['/orders/save']);
  }
}
