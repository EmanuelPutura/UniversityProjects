import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import {HttpClientModule} from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { NavigationBarComponent } from './navigation-bar/navigation-bar.component';
import { ClientsMenuComponent } from './clients-menu/clients-menu.component';
import { TechniciansMenuComponent } from './technicians-menu/technicians-menu.component';
import { DevicesMenuComponent } from './devices-menu/devices-menu.component';
import { RepairOrdersMenuComponent } from './repair-orders-menu/repair-orders-menu.component';
import { ClientsListComponent } from './clients-menu/clients-list/clients-list.component';
import { ClientsInsertComponent } from './clients-menu/clients-insert/clients-insert.component';
import { ClientsDetailComponent } from './clients-menu/clients-detail/clients-detail.component';
import {FormsModule} from "@angular/forms";

@NgModule({
  declarations: [
    AppComponent,
    NavigationBarComponent,
    ClientsMenuComponent,
    TechniciansMenuComponent,
    DevicesMenuComponent,
    RepairOrdersMenuComponent,
    ClientsListComponent,
    ClientsInsertComponent,
    ClientsDetailComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }