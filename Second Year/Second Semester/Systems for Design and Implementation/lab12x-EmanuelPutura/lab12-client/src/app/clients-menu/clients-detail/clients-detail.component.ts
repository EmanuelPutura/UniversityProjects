import {Component, Input, OnInit} from '@angular/core';
import {Client} from "../model/client";
import {ClientsService} from "../service/clients.service";
import {ActivatedRoute, Params} from "@angular/router";
import {switchMap} from "rxjs";
import {Location} from '@angular/common';


@Component({
  selector: 'app-clients-detail',
  templateUrl: './clients-detail.component.html',
  styleUrls: ['./clients-detail.component.css']
})
export class ClientsDetailComponent implements OnInit {
  @Input() client: Client | undefined;

  constructor(private clientsService: ClientsService,
              private route: ActivatedRoute,
              private location: Location) {
  }

  ngOnInit(): void {
    this.route.params
      .pipe(switchMap((params: Params) => this.clientsService.getClient(+ params['id'])))
      .subscribe(client => this.client = client);
  }

  goBack(): void {
    this.location.back();
  }

  save(): void {
    if (this.client) {
      this.clientsService.update(this.client)
        .subscribe(_ => this.goBack());
    }
  }

  delete(): void {
    if (this.client) {
      this.clientsService.delete(this.client).subscribe(_ => this.goBack());
    }
  }
}
