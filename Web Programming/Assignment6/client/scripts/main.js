class EventHandling {
    constructor() {
        this.pageSize = 4;
        this.currentPage = 0;
        const thisObject = this;

        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);
        document.getElementById("select-btn").addEventListener("click", function() {
            thisObject.loadProducts(thisObject);
        });

        this.loadProducts(this);
    }

    homeBtnClicked(event) {
        document.location.href = "./index.html";
    }

    dbInsertBtnClicked(event) {
        console.log("Hey!");
        document.location.href = "./client/pages/insert.html";
    }

    dbUpdateBtnClicked(event) {
        document.location.href = "./client/pages/update.html";
    }

    dbDeleteBtnClicked(event) {
        document.location.href = "./client/pages/delete.html";
    }

    loadProducts(thisObject) {
        const getRequest = new XMLHttpRequest();
        getRequest.open("GET", "./server/controller/controller.php?func=select&pageSize=" + thisObject.pageSize + "&currentPage=" + thisObject.currentPage, true);
        getRequest.send();

        thisObject.currentPage++;
    }
}
