class EventHandling {
    constructor() {
        this.currentPage = 0;

        const thisObject = this;
        this.basketProductIds = [];
        this.basketLabelStartText = "Shopping basket Product IDs: ";

        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);

        document.getElementById("submit-select-btn").addEventListener("click", function () {
            thisObject.currentPage = 0;
            const category = document.getElementById("select-category").value;
            thisObject.loadProducts(thisObject, category);
        });

        document.getElementById("prev-products-btn").addEventListener("click", function () {
            thisObject.currentPage--;
            const category = document.getElementById("select-category").value;
            thisObject.loadProducts(thisObject, category);
        });

        document.getElementById("next-products-btn").addEventListener("click", function () {
            thisObject.currentPage++;
            const category = document.getElementById("select-category").value;
            thisObject.loadProducts(thisObject, category);
        });

        document.getElementById("cart-add-btn").addEventListener("click", function () {
            thisObject.addToBasket(thisObject);
        });

        document.getElementById("cart-remove-btn").addEventListener("click", function () {
            thisObject.removeFromBasket(thisObject);
        });

        this.loadProducts(this, "");
    }

    homeBtnClicked(event) {
        document.location.href = "./Products";
    }

    dbInsertBtnClicked(event) {
        document.location.href = "./InsertProduct";
    }

    dbUpdateBtnClicked(event) {
        document.location.href = "./UpdateProduct";
    }

    dbDeleteBtnClicked(event) {
        document.location.href = "./DeleteProduct";
    }

    loadProducts(thisObject, category) {
        const getRequest = new XMLHttpRequest();
        getRequest.open("GET", "./Products/Products?category=" + category + "&currentPage=" + thisObject.currentPage, true);
        getRequest.send();

        getRequest.onload = function () {
            const decodedResult = JSON.parse(this.responseText);
            thisObject.currentPage = decodedResult.Item1;
            document.getElementById("main-products-div").innerHTML = decodedResult.Item2;
        }
    }

    addToBasket(thisObject) {
        const id = document.getElementById("select-cart-id").value;

        const getRequest = new XMLHttpRequest();
        getRequest.open("GET", "./CheckProductId?id=" + id, true);
        getRequest.send();

        getRequest.onload = function () {
            if (this.responseText.replace(/[^a-z]/gi, '') == "True") {
                if (thisObject.basketProductIds.indexOf(id) == -1) {
                    thisObject.basketProductIds.push(id);
                    thisObject.updateShoppingBasket();
                }
            }
            else {
                alert("Invalid ID!");
            }
        }
    }

    removeFromBasket(thisObject) {
        const id = document.getElementById("select-cart-id").value;

        const getRequest = new XMLHttpRequest();
        getRequest.open("GET", "./CheckProductId?id=" + id, true);
        getRequest.send();

        getRequest.onload = function () {
            if (this.responseText.replace(/[^a-z]/gi, '') == "True") {
                const idIndex = thisObject.basketProductIds.indexOf(id);
                if (idIndex != -1) {
                    thisObject.basketProductIds.splice(idIndex, 1);  // remove element from array
                    thisObject.updateShoppingBasket();
                }
                else {
                    alert("The product was not added to the shopping basket!");
                }
            }
            else {
                alert("Invalid ID!");
            }
        }
    }

    updateShoppingBasket() {
        let basketLabelText = this.basketLabelStartText;
        if (this.basketProductIds.length > 0)
            basketLabelText += this.basketProductIds[0];

        for (let i = 1; i < this.basketProductIds.length; ++i)
            basketLabelText += ", " + this.basketProductIds[i];

        document.getElementById("basket-label").innerHTML = basketLabelText;
    }
}
