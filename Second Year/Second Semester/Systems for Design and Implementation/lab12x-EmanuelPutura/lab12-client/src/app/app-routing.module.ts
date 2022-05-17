import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {ClientsMenuComponent} from "./clients-menu/clients-menu.component";
import {TechniciansMenuComponent} from "./technicians-menu/technicians-menu.component";
import {DevicesMenuComponent} from "./devices-menu/devices-menu.component";
import {RepairOrdersMenuComponent} from "./repair-orders-menu/repair-orders-menu.component";
import {ClientsDetailComponent} from "./clients-menu/clients-detail/clients-detail.component";

const routes: Routes = [
  // { path: '', component: ProductsComponent },
  { path: 'clients', component: ClientsMenuComponent },
  {path: 'clients/details/:id', component: ClientsDetailComponent},
  { path: 'technicians', component: TechniciansMenuComponent },
  { path: 'devices', component: DevicesMenuComponent },
  { path: 'orders', component: RepairOrdersMenuComponent }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
