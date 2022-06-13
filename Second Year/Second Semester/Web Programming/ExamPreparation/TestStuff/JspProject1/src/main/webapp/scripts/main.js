function doCrudGet(backendUrl, frontendUrl) {
    const getRequest = new XMLHttpRequest();
    getRequest.open("GET", backendUrl, true);
    getRequest.send();

    getRequest.onload = function() {
        document.location.href = frontendUrl;
        // document.open("text/html", "replace");
        // document.write(this.responseText);
        // document.close();
    }
}

function onInsertMenuBtnClicked() {
    doCrudGet("../crud?action=insert", "../pages/insert.jsp");
}

function onUpdateMenuBtnClicked() {
    doCrudGet("../crud?action=update", "../pages/update.jsp");
}

function onDeleteMenuBtnClicked() {
    doCrudGet("../crud?action=delete", "../pages/delete.jsp");
}
