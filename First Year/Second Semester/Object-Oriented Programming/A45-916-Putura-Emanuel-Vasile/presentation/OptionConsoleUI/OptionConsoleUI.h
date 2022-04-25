//
// Created by Emanuel on 23.03.2021.
//

#ifndef OPTIONCONSOLEUI_H
#define OPTIONCONSOLEUI_H

#include "../GenericConsoleUI/ConsoleUI.h"

class OptionConsoleUI : public ConsoleUI {
private:
    size_t exit_code; // 0 for exit, 1 for admin mode, 2 for user mode
    int mapCommand(const std::string& command) const;
public:
    OptionConsoleUI(CoatsService service) : exit_code(0), ConsoleUI(service) {}

    void menu() const override;
    int run() override;

    inline int getExitCode() const { return exit_code; }
};

#endif
