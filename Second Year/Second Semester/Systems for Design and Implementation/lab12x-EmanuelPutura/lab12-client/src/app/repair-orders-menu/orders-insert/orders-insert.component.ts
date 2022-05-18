import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {RepairOrdersService} from "../service/repair-orders.service";

@Component({
  selector: 'app-orders-insert',
  templateUrl: './orders-insert.component.html',
  styleUrls: ['./orders-insert.component.css']
})
export class OrdersInsertComponent implements OnInit {
  constructor(private ordersService: RepairOrdersService, private router: Router) {
  }

  ngOnInit(): void {
  }

  saveOrder(technicianId: string, deviceId: string) {
    const technicianIdNumber: number = Number(technicianId);
    if (isNaN(technicianIdNumber) || technicianIdNumber < 0) {
      alert("Order technician ID must be a positive number!");
      return;
    }

    const deviceIdNumber: number = Number(deviceId);
    if (isNaN(deviceIdNumber) || deviceIdNumber < 0) {
      alert("Order device ID must be a positive number!");
      return;
    }

    this.ordersService.save({technicianId: technicianIdNumber, deviceId: deviceIdNumber})
      .subscribe(_ => this.router.navigate(['/orders']), error => alert("Error: Invalid order data!"));
  }
}
