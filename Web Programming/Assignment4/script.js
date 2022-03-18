var moveCount = 0;
var running = true;

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

// returns 1 if the current player won the game, 0 if draw, -1 otherwise
function checkWinner(player, lastMoveX, lastMoveY) {
    // check for draw
    if (moveCount == 9) {
        return 0;
    }

    // check row constraints
    for (i = 1; i <= 3; ++i) {
        if (getButtonText(i, lastMoveY) != player) {
            break;
        }
        if (i == 3) {
            return 1;
        }
    }

    // check column constraints
    for (j = 1; j <= 3; ++j) {
        if (getButtonText(lastMoveX, j) != player) {
            break;
        }
        if (j == 3) {
            return 1;
        }
    }

    // check diagonal constraints
    if (lastMoveX == lastMoveY) {
        for (k = 1; k <= 3; ++k) {
            if (getButtonText(k, k) != player) {
                break;
            }
            if (k == 3) {
                return 1;
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
                return 1;
            }
        }
    }

    return -1;
}

// returns true if the game ended
function move(sign, x, y) {
    moveCount++;

    const gameState = checkWinner(sign, x, y);
    if (gameState == 0) {
        window.alert("Draw!");
        return true;
    }
    if (gameState == 1) {
        window.alert("Player " + sign + " has won the game!");
        return true;
    }

    return false;
}

function buttonClicked(button) {
    if (!running) {
        return;
    }

    const buttonXY = getButtonIDCoordinates(button.id);
    const buttonX = buttonXY[0];
    const buttonY = buttonXY[1];

    if (button.innerHTML == "X") {
        window.alert("Invalid move!");
    }
    else {
        button.innerHTML = "X";
        if (move("X", buttonX, buttonY)) {
            running =  false;
            return;
        }
    }

    const freeCells = buttonIds.filter((value) => document.getElementById(value).innerHTML == "");
    const aiLastCell = freeCells[0];

    document.getElementById(aiLastCell).innerHTML = "O";
    const aiCoordinates = getButtonIDCoordinates(aiLastCell);

    if (move("O", aiCoordinates[0], aiCoordinates[1])) {
        running = false;
        return;
    }
}
