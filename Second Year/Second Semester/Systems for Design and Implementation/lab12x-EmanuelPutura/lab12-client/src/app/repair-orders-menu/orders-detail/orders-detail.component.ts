import {Component, Input, OnInit} from '@angular/core';
import {ActivatedRoute, Params} from "@angular/router";
import {Location} from "@angular/common";
import {switchMap} from "rxjs";
import {RepairOrder} from "../model/repair-order";
import {RepairOrdersService} from "../service/repair-orders.service";

@Component({
  selector: 'app-orders-detail',
  templateUrl: './orders-detail.component.html',
  styleUrls: ['./orders-detail.component.css']
})
export class OrdersDetailComponent implements OnInit {
  @Input() order: RepairOrder | undefined;

  constructor(private ordersService: RepairOrdersService, private route: ActivatedRoute, private location: Location) {
  }

  ngOnInit(): void {
    this.route.params
      .pipe(switchMap((params: Params) => this.ordersService.getOrder(+ params['technicianId'], + params['deviceId'])))
      .subscribe(order => this.order = order);
  }

  goBack(): void {
    this.location.back();
  }

  delete(): void {
    if (this.order) {
      this.ordersService.delete(this.order).subscribe(_ => this.goBack());
    }
  }
}
