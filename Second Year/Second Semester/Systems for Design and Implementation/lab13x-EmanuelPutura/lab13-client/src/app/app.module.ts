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
import { TechniciansDetailComponent } from './technicians-menu/technicians-detail/technicians-detail.component';
import { TechniciansInsertComponent } from './technicians-menu/technicians-insert/technicians-insert.component';
import { TechniciansListComponent } from './technicians-menu/technicians-list/technicians-list.component';
import { DevicesListComponent } from './devices-menu/devices-list/devices-list.component';
import { DevicesInsertComponent } from './devices-menu/devices-insert/devices-insert.component';
import { DevicesDetailComponent } from './devices-menu/devices-detail/devices-detail.component';
import { DevicesAssociatedWithListComponent } from './devices-menu/devices-associated-with-list/devices-associated-with-list.component';
import { TechniciansAssociatedWithListComponent } from './technicians-menu/technicians-associated-with-list/technicians-associated-with-list.component';
import { ClientsSortedFilteredListComponent } from './clients-menu/clients-sorted-filtered-list/clients-sorted-filtered-list.component';
import { ClientsPaginatedComponent } from './clients-menu/clients-paginated/clients-paginated.component';
import { DevicesPaginatedComponent } from './devices-menu/devices-paginated/devices-paginated.component';
import { TechniciansPaginatedComponent } from './technicians-menu/technicians-paginated/technicians-paginated.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {MatButtonToggleModule} from "@angular/material/button-toggle";
import {MatCardModule} from "@angular/material/card";
import {MatSlideToggleModule} from "@angular/material/slide-toggle";
import {MatFormFieldModule} from "@angular/material/form-field";
import {MatSelectModule} from "@angular/material/select";
import { DevicesFromManyToManyComponent } from './devices-menu/devices-from-many-to-many/devices-from-many-to-many.component';
import { WorkshopTeamsMenuComponent } from './workshop-teams-menu/workshop-teams-menu.component';
import { WorkshopTeamsDetailComponent } from './workshop-teams-menu/workshop-teams-detail/workshop-teams-detail.component';
import { WorkshopTeamsInsertComponent } from './workshop-teams-menu/workshop-teams-insert/workshop-teams-insert.component';
import { WorkshopTeamsListComponent } from './workshop-teams-menu/workshop-teams-list/workshop-teams-list.component';
import { WorkshopTeamsPaginatedComponent } from './workshop-teams-menu/workshop-teams-paginated/workshop-teams-paginated.component';

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
    ClientsDetailComponent,
    TechniciansDetailComponent,
    TechniciansInsertComponent,
    TechniciansListComponent,
    DevicesListComponent,
    DevicesInsertComponent,
    DevicesDetailComponent,
    DevicesAssociatedWithListComponent,
    TechniciansAssociatedWithListComponent,
    ClientsSortedFilteredListComponent,
    ClientsPaginatedComponent,
    DevicesPaginatedComponent,
    TechniciansPaginatedComponent,
    DevicesFromManyToManyComponent,
    WorkshopTeamsMenuComponent,
    WorkshopTeamsDetailComponent,
    WorkshopTeamsInsertComponent,
    WorkshopTeamsListComponent,
    WorkshopTeamsPaginatedComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    FormsModule,
    HttpClientModule,
    BrowserAnimationsModule,
    MatButtonToggleModule,
    MatCardModule,
    MatSlideToggleModule,
    MatFormFieldModule,
    MatSelectModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
