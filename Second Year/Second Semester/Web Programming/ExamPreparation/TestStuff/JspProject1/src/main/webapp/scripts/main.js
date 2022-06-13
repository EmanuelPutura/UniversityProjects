function doCrudGet(url) {
    const getRequest = new XMLHttpRequest();
    getRequest.open("GET", url, true);
    getRequest.send();

    getRequest.onload = function() {
        document.open("text/html", "replace");
        document.write(this.responseText);
        document.close();
    }
}

function onInsertMenuBtnClicked() {
    doCrudGet("../crud?action=insert");
}

function onUpdateMenuBtnClicked() {
    doCrudGet("../crud?action=update");
}

function onDeleteMenuBtnClicked() {
    doCrudGet("../crud?action=delete");
}
