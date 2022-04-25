class EventHandling {
    constructor() {
        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);

        document.getElementById("submit-update-btn").addEventListener("click", this.submitBtnClicked);
    }

    homeBtnClicked(event) {
        document.location.href = "../../index.html";
    }

    dbInsertBtnClicked(event) {
        console.log("Hey!");
        document.location.href = "./insert.html";
    }

    dbUpdateBtnClicked(event) {
        document.location.href = "./update.html";
    }

    dbDeleteBtnClicked(event) {
        document.location.href = "./delete.html";
    }

    submitBtnClicked(event) {
        const productID = document.getElementById("product-id").value;
        const productName = document.getElementById("product-name").value;
        const productCategory = document.getElementById("product-category").value;
        const productPrice = document.getElementById("product-price").value;

        const requestContent = {"func": "update", "productID": productID, "productName": productName, "productCategory": productCategory, "productPrice": productPrice};
        const putRequestBody = JSON.stringify(requestContent);
        const putRequest = new XMLHttpRequest();

        // putRequest.onload = function() {
        //     console.log(this.responseText);
        // }

        putRequest.open("PUT", "../../server/controller/controller.php");
        putRequest.setRequestHeader("Content-type", "application/json");
        putRequest.send(putRequestBody);
    }
}
