import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {ClientsMenuComponent} from "./clients-menu/clients-menu.component";
import {TechniciansMenuComponent} from "./technicians-menu/technicians-menu.component";
import {DevicesMenuComponent} from "./devices-menu/devices-menu.component";
import {RepairOrdersMenuComponent} from "./repair-orders-menu/repair-orders-menu.component";
import {ClientsDetailComponent} from "./clients-menu/clients-detail/clients-detail.component";
import {ClientsInsertComponent} from "./clients-menu/clients-insert/clients-insert.component";
import {TechniciansInsertComponent} from "./technicians-menu/technicians-insert/technicians-insert.component";
import {TechniciansDetailComponent} from "./technicians-menu/technicians-detail/technicians-detail.component";
import {DevicesInsertComponent} from "./devices-menu/devices-insert/devices-insert.component";
import {DevicesDetailComponent} from "./devices-menu/devices-detail/devices-detail.component";
import {OrdersDetailComponent} from "./repair-orders-menu/orders-detail/orders-detail.component";
import {OrdersInsertComponent} from "./repair-orders-menu/orders-insert/orders-insert.component";

const routes: Routes = [
  { path: 'clients', component: ClientsMenuComponent },
  { path: 'clients/details/:id', component: ClientsDetailComponent},
  { path: 'clients/save', component: ClientsInsertComponent},

  { path: 'technicians', component: TechniciansMenuComponent },
  { path: 'technicians/details/:id', component: TechniciansDetailComponent},
  { path: 'technicians/save', component: TechniciansInsertComponent},

  { path: 'devices', component: DevicesMenuComponent },
  { path: 'devices/details/:id', component: DevicesDetailComponent},
  { path: 'devices/save', component: DevicesInsertComponent},

  { path: 'orders', component: RepairOrdersMenuComponent },
  { path: 'orders/details/:technicianId/:deviceId', component: OrdersDetailComponent},
  { path: 'orders/save', component: OrdersInsertComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
