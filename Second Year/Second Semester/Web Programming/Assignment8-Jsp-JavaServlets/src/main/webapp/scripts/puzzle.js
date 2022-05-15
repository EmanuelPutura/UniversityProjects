function onLogoutButtonClicked() {
    const getRequest = new XMLHttpRequest();
    const url = "../puzzle-controller?action=disconnect";

    getRequest.open("GET", url, true);
    getRequest.send();
}

function onPieceDivClicked(divId) {
    const getRequest = new XMLHttpRequest();
    const url = "../puzzle-controller?action=click&htmlId=" + divId;

    getRequest.open("GET", url, true);
    getRequest.send();

    getRequest.onload = function() {
        const resultObj = JSON.parse(this.responseText);

        if (resultObj.status === "OK") {
            document.getElementById(resultObj.firstDivId).style.backgroundImage = resultObj.firstDivImg;
            document.getElementById(resultObj.secondDivId).style.backgroundImage = resultObj.secondDivImg;

            if (resultObj.win === "true") {
                const movesPerformed = resultObj.moves;
                alert("Congratulations, you've completed the puzzle in " + movesPerformed + " moves!");
            }
        }
    }
}

function createDivs() {
    for (let i = 0; i < 3; ++i) {
        for (let j = 0; j < 3; ++j) {
            let pieceDiv = document.createElement("div");
            pieceDiv.id = "piece" + i.toString() + j.toString();
            document.getElementById("puzzle-table").appendChild(pieceDiv)

            pieceDiv.onclick = function() {
                onPieceDivClicked(pieceDiv.id);
            }
        }
    }

    fetchPieces();
}

function fetchPieces() {
    const getRequest = new XMLHttpRequest();
    getRequest.open("GET", "../puzzle-controller?action=fetch", true);
    getRequest.send();

    getRequest.onload = function() {
        const resultArray = JSON.parse(this.responseText);
        resultArray.forEach(piece => {
            const divId = piece["htmlId"];
            const cssBackgroundImgUrl = piece["cssBackgroundImg"];

            document.getElementById(divId).style.backgroundImage = cssBackgroundImgUrl;
        });
    }
}

window.onload = createDivs;
