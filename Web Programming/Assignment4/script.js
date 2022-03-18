function buttonClicked(button) {
    if (button.innerHTML == "X")
        window.alert("Invalid move!");
    else
        button.innerHTML = "X";

    buttonIds = [];
    for (i = 1; i <= 3; ++i) {
        for (j = 1; j <= 3; ++j) {
            buttonIds.push("btn" + String(i) + String(j));
        }
    }

    const freeCells = buttonIds.filter((value) => document.getElementById(value).innerHTML == "");
    document.getElementById(freeCells[0]).innerHTML = "O";
}
