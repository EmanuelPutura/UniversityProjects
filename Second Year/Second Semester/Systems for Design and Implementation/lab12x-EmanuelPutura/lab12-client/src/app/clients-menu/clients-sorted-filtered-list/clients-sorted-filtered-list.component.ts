import {Component, OnInit} from '@angular/core';
import {Client} from "../model/client";
import {ClientsService} from "../service/clients.service";
import {Router} from "@angular/router";

@Component({
  selector: 'app-clients-sorted-filtered-list',
  templateUrl: './clients-sorted-filtered-list.component.html',
  styleUrls: ['./clients-sorted-filtered-list.component.css']
})
export class ClientsSortedFilteredListComponent implements OnInit {
  errorMessage: string;
  clients: Array<Client>;

  constructor(private clientsService: ClientsService, private router: Router) {
  }

  ngOnInit(): void {
  }

  getClientsSortedAndFiltered(filterField: string, sortingField: string): void {
    this.clientsService.getClientsSortedAndFiltered(filterField, sortingField)
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
