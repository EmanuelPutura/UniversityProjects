class EventHandling {
    constructor() {
        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);

        document.getElementById("submit-insert-btn").addEventListener("click", this.submitBtnClicked);
    }

    homeBtnClicked(event) {
        document.location.href = "./";
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

    submitBtnClicked(event) {
        const productName = document.getElementById("product-name").value;
        const productCategory = document.getElementById("product-category").value;
        const productPrice = document.getElementById("product-price").value;

        const postRequestBody = "productName=" + productName + "&productCategory=" + productCategory + "&productPrice=" + productPrice;
        const postRequest = new XMLHttpRequest();

        postRequest.open("POST", "./InsertProductPersist");
        postRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        postRequest.send(postRequestBody);
    }
}
