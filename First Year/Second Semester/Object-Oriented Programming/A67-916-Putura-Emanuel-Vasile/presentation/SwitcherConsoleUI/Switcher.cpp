//
// Created by Emanuel on 25.03.2021.
//

#include "Switcher.h"

void Switcher::run() {
    int exit_code = 1;

    while(exit_code == 1) {
        exit_code = mainConsole.run();
        if (exit_code == 1)
            exit_code = childConsole.run();
    }
}

