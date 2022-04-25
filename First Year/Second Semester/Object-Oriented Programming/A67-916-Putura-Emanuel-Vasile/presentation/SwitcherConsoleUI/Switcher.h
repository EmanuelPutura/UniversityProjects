//
// Created by Emanuel on 25.03.2021.
//

#ifndef SWITCHER_H
#define SWITCHER_H

#include "../GenericConsoleUI/ConsoleUI.h"

class Switcher {
private:
    ConsoleUI& mainConsole;
    ConsoleUI& childConsole;
public:
    Switcher(ConsoleUI& mainConsole, ConsoleUI& childConsole) : mainConsole(mainConsole), childConsole(childConsole) {}
    void run();
};

#endif
