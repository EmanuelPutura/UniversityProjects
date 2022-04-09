class EventHandling {
    constructor() {
        document.getElementById("home-page").addEventListener("click", this.homeBtnClicked);
        document.getElementById("db-insert").addEventListener("click", this.dbInsertBtnClicked);
        document.getElementById("db-update").addEventListener("click", this.dbUpdateBtnClicked);
        document.getElementById("db-delete").addEventListener("click", this.dbDeleteBtnClicked);
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
}
