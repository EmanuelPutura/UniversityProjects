import {Client} from "../model/client";
import {Router} from "@angular/router";
import {ClientsService} from "../service/clients.service";
import {Component, OnInit} from "@angular/core";

@Component({
  selector: 'app-clients-list',
  templateUrl: './clients-list.component.html',
  styleUrls: ['./clients-list.component.css']
})
export class ClientsListComponent implements OnInit {
  errorMessage: string;
  clients: Array<Client>;
  selectedClient: Client;

  constructor(private clientsService: ClientsService,
              private router: Router) {
  }

  ngOnInit(): void {
    this.getClients();
  }

  getClients(): void {
    this.clientsService.getClients()
      .subscribe(
        clients => {
          this.clients = clients
        },
        error => this.errorMessage = <any>error
      );
  }

  onSelect(student: Client): void {
    this.selectedClient = student;
  }

  gotoDetail(): void {
    this.router.navigate(['/clients/details', this.selectedClient.id]);
  }
}
