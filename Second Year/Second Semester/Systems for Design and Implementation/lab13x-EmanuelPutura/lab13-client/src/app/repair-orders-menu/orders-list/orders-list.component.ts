import { Component, OnInit } from '@angular/core';
import {Router} from "@angular/router";
import {RepairOrder} from "../model/repair-order";
import {RepairOrdersService} from "../service/repair-orders.service";

@Component({
  selector: 'app-orders-list',
  templateUrl: './orders-list.component.html',
  styleUrls: ['./orders-list.component.css']
})
export class OrdersListComponent implements OnInit {
  errorMessage: string;
  orders: Array<RepairOrder>;
  selectedOrder: RepairOrder;

  constructor(private ordersService: RepairOrdersService, private router: Router) {
  }

  ngOnInit(): void {
    this.getOrders();
  }

  getOrders(): void {
    this.ordersService.getOrders()
      .subscribe(
        orders => {
          this.orders = orders
        },
        error => this.errorMessage = <any>error
      );
  }

  onSelect(order: RepairOrder): void {
    this.selectedOrder = order;
  }

  gotoDetail(): void {
    this.router.navigate(['/orders/details', this.selectedOrder.technicianId, this.selectedOrder.deviceId]);
  }
}
