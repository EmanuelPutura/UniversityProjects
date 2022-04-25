//
// Created by Emanuel on 23.03.2021.
//

#ifndef OPTIONCONSOLEUI_H
#define OPTIONCONSOLEUI_H

#include "../GenericConsoleUI/ConsoleUI.h"

#include <string>

class OptionConsoleUI {
private:
    size_t basket_type; // 0 for CSV files, 1 for HTML files
    size_t exit_code;   // 0 for exit, 1 for admin mode, 2 for user mode

    int mapCommand(const std::string& command) const;
    std::string getCommand() const;
    std::string getUserData(const std::string& message) const;
    bool isPositiveInteger(const std::string& string) const;
public:
    OptionConsoleUI() : exit_code(0), basket_type(0) {}

    void menu() const;
    int run();

    inline int getExitCode() const { return exit_code; }
    inline int getBasketType() const { return basket_type; }
};

#endif
