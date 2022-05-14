function shuffle(array) {
    let currentIndex = array.length,  randomIndex;

    // While there remain elements to shuffle.
    while (currentIndex !== 0) {

        // Pick a remaining element.
        randomIndex = Math.floor(Math.random() * currentIndex);
        currentIndex--;

        // And swap it with the current element.
        [array[currentIndex], array[randomIndex]] = [
            array[randomIndex], array[currentIndex]];
    }

    return array;
}

function coordinatesSetup() {
    let coordinates = []
    for (let i = 0; i < 3; ++i) {
        for (let j = 0; j < 3; ++j) {
            coordinates.push([i, j]);
        }
    }

    return shuffle(coordinates);
}

function setPieces() {
    let coordinates = coordinatesSetup();

    for (let index = 0; index < 9; ++index) {
        let pieceDiv = document.createElement("div");
        pieceDiv.style.backgroundImage = "url(../resources/images/image" + coordinates[index][0].toString() + coordinates[index][1].toString() + ".jpg)";
        document.getElementById("puzzle-table").appendChild(pieceDiv)
    }
}

window.onload = setPieces;
