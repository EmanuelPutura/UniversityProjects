import { Injectable } from '@angular/core';
import { Component, OnInit } from '@angular/core';

import { Product } from '../domain/product';

@Component({
    selector: 'app-products-table',
    templateUrl: './products-table.component.html',
    styleUrls: ['./products-table.component.scss']
})
@Injectable({
    providedIn: 'root'
})
export class ProductsTableComponent implements OnInit {
    constructor() { }

    ngOnInit(): void {
    }

    updateProducts(products: Product[], pageSize: number, currentPage: number): number {
        let table = document.getElementById('products-table');
        if (table == null) {
            throw new Error("Table element not found!");
        }

        let tableElement: HTMLTableElement = table as HTMLTableElement;
        let jsonAttributeNames = ["id", "name", "category", "price"];

        for (let page = 1; page <= pageSize; ++page) {
            for (let column = 0, m = tableElement.rows[page].cells.length; column < m; column++) {
                tableElement.rows[page].cells[column].innerHTML = "";
            }
        }

        for (let row = 1, n = tableElement.rows.length; row < n; row++) {
            if (products[row - 1] == undefined || products[row - 1].id == undefined)
                tableElement.rows[row].cells[0].innerHTML = "";
            else
                tableElement.rows[row].cells[0].innerHTML = products[row - 1].id.toString();
    
            if (products[row - 1] == undefined || products[row - 1].name == undefined)
                tableElement.rows[row].cells[1].innerHTML = "";
            else tableElement.rows[row].cells[1].innerHTML = products[row - 1].name;

            if (products[row - 1] == undefined || products[row - 1].category == undefined)
                tableElement.rows[row].cells[2].innerHTML = "";
            else tableElement.rows[row].cells[2].innerHTML = products[row - 1].category;

            if (products[row - 1] == undefined || products[row - 1].price == undefined)
                tableElement.rows[row].cells[3].innerHTML = "";
            else tableElement.rows[row].cells[3].innerHTML = products[row - 1].price.toString();
        }

        return parseInt(products[products.length - 1].toString());
    }
}
