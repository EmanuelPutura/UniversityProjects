//
// Created by Emanuel on 23.03.2021.
//

#include "OptionConsoleUI.h"
#include "../../exceptions/ServiceException/ServiceException.h"

#include <iostream>

void OptionConsoleUI::menu() const {
    TextTable table {2};
    table.addHeader(2, "COMMAND", "COMMAND DESCRIPTION");
    table.addRow(2, "admin", "open the application in admin mode");
    table.addRow(2, "user", "open the application in user mode");
    table.addRow(2, "exit", "exit the application");
    std::cout << table << '\n';
}

int OptionConsoleUI::run() {
    bool running = true;
    while(running) {
        menu();
        int command = mapCommand(getCommand());

        try {
            switch (command) {
                case 0:
                    // admin case
                    exit_code = 1;
                    running = false;
                    break;
                case 1:
                    // user case
                    exit_code = 2;
                    running = false;
                    break;
                case 2:
                    // exit case
                    running = false;
                    break;
                default:
                    std::cout << "Invalid command.\n";
                    break;
            }
        }
        catch (const ServiceException& exception) {
            std::cout << exception.getMessage();
        }
        catch (const RepositoryException& exception) {
            std::cout << exception.getMessage();
        }
        catch (...) {
            std::cout << "Unexpected exception occurred!\n";
        }
    }
    return 0;
}

int OptionConsoleUI::mapCommand(const std::string &command) const {
    std::string commands[] = {"admin", "user", "exit"};
    int int_commands[] = {0, 1, 2};

    for (size_t i = 0; i < 3; ++i)
        if (command == commands[i]) return int_commands[i];
    return -1;
}

