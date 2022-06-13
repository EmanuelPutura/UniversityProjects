class EventHandling {
    constructor() {
        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);

        this.addRowHandlers();
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
        const productID = document.getElementById("product-id").value;
        const productName = document.getElementById("product-name").value;
        const productCategory = document.getElementById("product-category").value;
        const productPrice = document.getElementById("product-price").value;

        const requestContent = { "func": "update", "productID": productID, "productName": productName, "productCategory": productCategory, "productPrice": productPrice };
        const putRequestBody = JSON.stringify(requestContent);
        const putRequest = new XMLHttpRequest();


        putRequest.open("PUT", "../../server/controller/controller.php");
        putRequest.setRequestHeader("Content-type", "application/json");
        putRequest.send(putRequestBody);
    }

    rowHandler(row) {
        const cellTdElements = row.getElementsByTagName("td");
        if (cellTdElements.length < 3) {
            return;
        }

        const productName = cellTdElements[0].innerHTML;
        const productCategory = cellTdElements[1].innerHTML;
        const productPrice = cellTdElements[2].innerHTML;

        const result = confirm("Want to delete?");
        if (!result) {
            return;
        }

        const getRequest = new XMLHttpRequest();
        getRequest.open("GET", "./DeleteProductPersist?name=" + productName + "&category=" + productCategory + "&price=" + productPrice, true);
        getRequest.send();

        getRequest.onload = function () {
            document.location.href = "./";
        }
    }

    addRowHandlers() {
        const table = document.getElementById("productsTable");
        const rows = table.getElementsByTagName("tr");
        const thisObject = this;

        for (var i = 0; i < rows.length; i++) {
            const currentRow = table.rows[i];

            currentRow.onclick = function () {
                thisObject.rowHandler(currentRow);
            };
        }
    }
}
