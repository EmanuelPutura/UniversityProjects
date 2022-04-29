import { Component, OnInit } from '@angular/core';
import { ProductsService } from '../products.service';

@Component({
    selector: 'app-update',
    templateUrl: './update.component.html',
    styleUrls: ['./update.component.scss']
})
export class UpdateComponent implements OnInit {
    private id: number = -1;
    private productName: string = "";
    private productCategory: string = "";
    private productPrice: number = 0;

    constructor(private productsService: ProductsService) { }

    ngOnInit(): void {
    }

    set productId(id: number) {
        this.id = id;
    }

    set name(name: string) {
        this.productName = name;
    }

    set category(category: string) {
        this.productCategory = category;
    }

    set price(price: number) {
        this.productPrice = price;
    }

    onUpdateButton(): void {

    }
}
