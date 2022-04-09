class EventHandling {
    constructor() {
        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);

        document.getElementById("submit-insert-btn").addEventListener("click", this.submitBtnClicked);
    }

    homeBtnClicked(event) {
        document.location.href = "../../index.html";
    }

    dbInsertBtnClicked(event) {
        document.location.href = "./insert.html";
    }

    dbUpdateBtnClicked(event) {
        document.location.href = "./update.html";
    }

    dbDeleteBtnClicked(event) {
        document.location.href = "./delete.html";
    }

    submitBtnClicked(event) {
        const productName = document.getElementById("product-name").value;
        const productCategory = document.getElementById("product-category").value;
        const productPrice = document.getElementById("product-price").value;

        const postRequestBody = "func=insert&productName=" + productName + "&productCategory=" + productCategory + "&productPrice=" + productPrice;
        const postRequest = new XMLHttpRequest();

        postRequest.onload = function() {
            console.log(this.responseText);
        }

        postRequest.open("POST", "../../server/controller/controller.php");
        postRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        postRequest.send(postRequestBody);
    }

    
}
