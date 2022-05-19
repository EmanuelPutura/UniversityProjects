import { Component, OnInit } from '@angular/core';
import {Client} from "../model/client";
import {ClientsService} from "../service/clients.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-clients-paginated',
  templateUrl: './clients-paginated.component.html',
  styleUrls: ['./clients-paginated.component.css']
})
export class ClientsPaginatedComponent implements OnInit {
  errorMessage: string;
  clients: Array<Client>;

  constructor(private clientsService: ClientsService, private router: Router) {
  }

  ngOnInit(): void {
  }

  getClientsPaginated(page: string, size: string): void {
    const pageNumber: number = Number(page);
    if (isNaN(pageNumber) || pageNumber < 0) {
      alert("Page number must be a positive number!");
      return;
    }

    const sizeNumber: number = Number(size);
    if (isNaN(sizeNumber) || sizeNumber < 0) {
      alert("Page size must be a positive number!");
      return;
    }

    this.clientsService.getClientsPaginated(pageNumber, sizeNumber)
      .subscribe(
        clients => {
          this.clients = clients
        },
        error => {
          this.errorMessage = <any>error;
          alert("Error: Invalid data given!");
        }
      );
  }
}
