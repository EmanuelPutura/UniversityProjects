class EventHandling {
    constructor() {
        this.pageSize = 4;
        this.currentPage = 0;
        const thisObject = this;

        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);
        
        document.getElementById("submit-select-btn").addEventListener("click", function() {
            thisObject.currentPage = 0;
            const category = document.getElementById("select-category").value;
            thisObject.loadProducts(thisObject, category);
        });

        document.getElementById("prev-products-btn").addEventListener("click", function() {
            thisObject.currentPage--;
            const category = document.getElementById("select-category").value;
            thisObject.loadProducts(thisObject, category);
        });
        
        document.getElementById("next-products-btn").addEventListener("click", function() {
            thisObject.currentPage++;
            const category = document.getElementById("select-category").value;
            thisObject.loadProducts(thisObject, category);
        });

        this.loadProducts(this);
    }

    homeBtnClicked(event) {
        document.location.href = "./index.html";
    }

    dbInsertBtnClicked(event) {
        document.location.href = "./client/pages/insert.html";
    }

    dbUpdateBtnClicked(event) {
        document.location.href = "./client/pages/update.html";
    }

    dbDeleteBtnClicked(event) {
        document.location.href = "./client/pages/delete.html";
    }

    loadProducts(thisObject, category) {
        const getRequest = new XMLHttpRequest();
        getRequest.open("GET", "./server/controller/controller.php?func=select&category=" + category + "&pageSize=" + thisObject.pageSize + "&currentPage=" + thisObject.currentPage, true);
        getRequest.send();

        let table = document.getElementById('products-table');
        let jsonAttributeNames = ["id", "name", "category", "price"];

        for (let page = 1; page <= thisObject.pageSize; ++page) {
            for (let column = 0, m = table.rows[page].cells.length; column < m; column++) {
                table.rows[page].cells[column].innerHTML = "";
            }
        }

        getRequest.onload = function() {
            const resultArray = JSON.parse(this.responseText);
            resultArray.forEach(function(current, index, array) {
                array[index] = JSON.parse(current);
            });
            
            for (let page = 1; page <= thisObject.pageSize; ++page) {
                for (let column = 0, m = table.rows[page].cells.length; column < m; column++) {
                    table.rows[page].cells[column].innerHTML = "";
                }
            }

            for (let row = 1, n = table.rows.length; row < n; row++) {
                for (let column = 0, m = table.rows[row].cells.length; column < m; column++) {
                    if (resultArray[row - 1] == undefined || resultArray[row - 1][jsonAttributeNames[column]] == undefined)
                        table.rows[row].cells[column].innerHTML = "";
                    else table.rows[row].cells[column].innerHTML = resultArray[row - 1][jsonAttributeNames[column]];
                }
            }

            thisObject.currentPage = resultArray[thisObject.pageSize];
        }
    }
}
