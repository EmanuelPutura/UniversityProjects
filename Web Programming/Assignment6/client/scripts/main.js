class EventHandling {
    constructor(insertBtnId, updateBtnId, deleteBtnId) {
        document.getElementById(insertBtnId).addEventListener("click", this.insertBtnClicked);
        document.getElementById(updateBtnId).addEventListener("click", this.updateBtnClicked);
        document.getElementById(deleteBtnId).addEventListener("click", this.deleteBtnClicked);
    }

    insertBtnClicked(event) {
        document.location.href = "./client/pages/insert.html";
    }

    updateBtnClicked(event) {
        console.log(event);
    }

    deleteBtnClicked(event) {
        console.log(event);
    }
}
