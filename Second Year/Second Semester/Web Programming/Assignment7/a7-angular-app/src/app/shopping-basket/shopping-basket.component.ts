import { Component, OnInit } from '@angular/core';
import { ProductsService } from '../products.service';

@Component({
    selector: 'app-shopping-basket',
    templateUrl: './shopping-basket.component.html',
    styleUrls: ['./shopping-basket.component.scss']
})
export class ShoppingBasketComponent implements OnInit {
    private toAddId: number = -1;
    private basketProductIds: number[] = [];
    private basketLabelStartText: string = "Shopping basket Product IDs: ";

    constructor(private productsService: ProductsService) { }

    set inputAddId(id: number) {
        this.toAddId = id;
    }

    ngOnInit(): void {
    }

    onAddToCartButton(): void {
        this.productsService.checkProductId(this.toAddId).subscribe(str => {
            const response: string = str[0];
            if (response.replace(/[^a-z]/gi, '') == "valid") {
                if (this.basketProductIds.indexOf(this.toAddId) == -1) {
                    this.basketProductIds.push(this.toAddId);
                    this.updateShoppingBasket();
                }
            }
            else {
                alert("Invalid ID!");
            }
        })
    }

    onRemoveFromCartButton(): void {
        this.productsService.checkProductId(this.toAddId).subscribe(str => {
            const response: string = str[0];
            if (response.replace(/[^a-z]/gi, '') == "valid") {
                const idIndex = this.basketProductIds.indexOf(this.toAddId);
                if (idIndex != -1) {
                    this.basketProductIds.splice(idIndex, 1);  // remove element from array
                    this.updateShoppingBasket();
                }
                else {
                    alert("The product was not added to the shopping basket!");
                }
            }
            else {
                alert("Invalid ID!");
            }
        })
    }

    updateShoppingBasket(): void {
        let basketLabelText = this.basketLabelStartText;
        if (this.basketProductIds.length > 0)
            basketLabelText += this.basketProductIds[0];
        
        for (let i = 1; i < this.basketProductIds.length; ++i)
            basketLabelText += ", " + this.basketProductIds[i];

        const basketLabel = document.getElementById("basket-label");
        if (basketLabel != null) {
            basketLabel.innerHTML = basketLabelText;
        }
    }
}
