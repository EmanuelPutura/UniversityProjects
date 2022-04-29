import { Component, OnInit } from '@angular/core';
import { ProductsService } from '../products.service';

@Component({
    selector: 'app-delete',
    templateUrl: './delete.component.html',
    styleUrls: ['./delete.component.scss']
})
export class DeleteComponent implements OnInit {
    private id: number = -1;

    constructor(private productsService: ProductsService) { }

    ngOnInit(): void {
    }

    set productId(id: number) {
        this.id = id;
    }

    onDeleteButton(): void {
        this.productsService.deleteProduct(this.id);
    }
}
