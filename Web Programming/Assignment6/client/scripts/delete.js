class EventHandling {
    constructor() {
        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);

        document.getElementById("submit-delete-btn").addEventListener("click", this.submitBtnClicked);
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
        const requestContent = {"func": "delete", "productID": productID};
        const deleteRequestBody = JSON.stringify(requestContent);
        const deleteRequest = new XMLHttpRequest();

        // deleteRequest.onload = function() {
        //     console.log(this.responseText);
        // }

        deleteRequest.open("DELETE", "../../server/controller/controller.php");
        deleteRequest.setRequestHeader("Content-type", "application/json");
        deleteRequest.send(deleteRequestBody);
    }
}
