import { Component, OnInit } from '@angular/core';
import { ProductsService } from '../products.service';

import { Product } from '../domain/product';
import { ProductsTableComponent } from '../products-table/products-table.component';
import { Observable } from 'rxjs';

@Component({
    selector: 'app-select-category',
    templateUrl: './select-category.component.html',
    styleUrls: ['./select-category.component.scss']
})
export class SelectCategoryComponent implements OnInit {
    private selectedCategory: string = "";

    private currentPage: number = 0;
    private pageSize: number = 4;

    private currentProducts: Product[] = [];

    constructor(private productsService: ProductsService, private productsTableComponent: ProductsTableComponent) { }

    get products(): Product[] {
        return this.currentProducts;
    }

    set page(currentPage: number) {
        this.currentPage = currentPage;
    }

    ngOnInit(): void {
    }

    get category(): string {
        return this.selectedCategory;
    }

    set category(category: string) {
        this.selectedCategory = category;
    }

    onSubmitCategoryButton(): void {
        this.currentPage = 0;
        this.loadProducts();
    }

    onPrevButton(): void {
        this.currentPage--;
        this.loadProducts();
    }

    onNextButton(): void {
        this.currentPage++;
        this.loadProducts();
    }

    private loadProducts(): void {
        const category: string = this.selectedCategory;
        let observales: Observable<Product[]> = this.productsService.fetchProducts(category, this.pageSize, this.currentPage);
        observales.subscribe(elements => {
            this.currentProducts = elements;
            this.currentProducts = this.currentProducts.map(el => JSON.parse(el.toString()));
            this.currentPage = this.productsTableComponent.updateProducts(this.currentProducts, this.pageSize, this.currentPage)
        });
    }
}
