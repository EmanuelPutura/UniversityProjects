import { Component, OnInit } from '@angular/core';
import { ProductsService } from '../products.service';

@Component({
    selector: 'app-insert',
    templateUrl: './insert.component.html',
    styleUrls: ['./insert.component.scss']
})
export class InsertComponent implements OnInit {
    private productName: string = "";
    private productCategory: string = "";
    private productPrice: number = 0;

    constructor(private productsService: ProductsService) { }

    set name(name: string) {
        this.productName = name;
    }

    set category(category: string) {
        this.productCategory = category;
    }

    set price(price: number) {
        this.productPrice = price;
    }

    ngOnInit(): void {
    }

    onSubmitInsertButton(): void {
        this.productsService.addProduct(this.productName, this.productCategory, this.productPrice);
    }
}
