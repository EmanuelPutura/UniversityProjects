import { Component, OnInit } from '@angular/core';
import {ClientsService} from "../service/clients.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-clients-insert',
  templateUrl: './clients-insert.component.html',
  styleUrls: ['./clients-insert.component.css']
})
export class ClientsInsertComponent implements OnInit {

  constructor(private clientsService: ClientsService, private router: Router) {
  }

  ngOnInit(): void {
  }

  saveClient(firstName: string, lastName: string, emailAddress: string) {
    this.clientsService.save({id: 0, firstName, lastName, emailAddress})
      .subscribe(_ => this.router.navigate(['/clients']));
  }
}
