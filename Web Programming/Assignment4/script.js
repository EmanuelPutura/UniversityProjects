var moveCount = 0;
const buttonIds = [];
for (i = 1; i <= 3; ++i) {
    for (j = 1; j <= 3; ++j) {
        buttonIds.push(createButtonID(i, j));
    }
}

function createButtonID(buttonX, buttonY) {
    return "btn" + String(buttonX) + String(buttonY);
}

function getButtonIDCoordinates(buttonID) {
    coordinates = buttonID.slice(-2);
    return [Number(coordinates[0]), Number(coordinates[1])];
}

function getButtonText(buttonX, buttonY) {
    return document.getElementById(createButtonID(buttonX, buttonY)).innerHTML;
}

function checkWinner(player, lastMoveX, lastMoveY) {
    // check row constraints
    for (i = 1; i <= 3; ++i) {
        if (getButtonText(i, lastMoveY) != player) {
            break;
        }
        if (i == 3) {
            return true;
        }
    }

    // check column constraints
    for (j = 1; j <= 3; ++j) {
        if (getButtonText(lastMoveX, j) != player) {
            break;
        }
        if (j == 3) {
            return true;
        }
    }

    // check diagonal constraints
    if (lastMoveX == lastMoveY) {
        for (k = 1; k <= 3; ++k) {
            if (getButtonText(k, k) != player) {
                break;
            }
            if (k == 3) {
                return true;
            }
        }
    }

    // check anti-diagonal constraints
    if (lastMoveX + lastMoveY == 4) {
        for (k = 1; k <= 3; ++k) {
            if (getButtonText(k, 4 - k) != player) {
                break;
            }
            if (k == 3) {
                return true;
            }
        }
    }

    return false;
}

function buttonClicked(button) {
    if (button.innerHTML == "X") {
        window.alert("Invalid move!");
    }
    else {
        button.innerHTML = "X";
    }

    const freeCells = buttonIds.filter((value) => document.getElementById(value).innerHTML == "");
    document.getElementById(freeCells[0]).innerHTML = "O";
}
