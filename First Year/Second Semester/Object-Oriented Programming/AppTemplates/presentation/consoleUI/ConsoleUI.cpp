//
// Created by Emanuel on 04.04.2021.
//

#include "ConsoleUI.h"

#include <iostream>

std::string ConsoleUI::getCommand() const {
    std::string command;
    std::cout << "command > ";
    std::getline(std::cin, command);
    std::cout << '\n';
    return command;
}

bool ConsoleUI::isPositiveInteger(const std::string& string) const {
    for (size_t i = 0; i < string.length(); ++i)
        if (!isdigit(string[i])) return false;
    return true;
}

std::string ConsoleUI::getUserData(const std::string& message) const {
    std::string user_data;
    std::cout << message << "\n> ";
    std::getline(std::cin, user_data);
    std::cout << '\n';
    return user_data;
}

int ConsoleUI::mapCommand(const std::string &command) const {
    std::string commands[] = {"exit"};
    int int_commands[] = {0};

    for (size_t i = 0; i < 1; ++i)
        if (command == commands[i]) return int_commands[i];
    return -1;
}

void ConsoleUI::menu() {
    // title
    for (size_t i = 0; i < 20; ++i)
        std::cout << '-';
    std::string title = " Test Application ";
    std::cout << title;
    for (size_t i = 0; i < 20; ++i)
        std::cout << '-';
    std::cout << '\n';

    // commands
    std::cout << "exit - exit the application\n";

    // ending
    for (size_t i = 0; i < 40 + title.size(); ++i)
        std::cout << '-';
    std::cout << '\n';
}

void ConsoleUI::run() {
    bool running = true;
    while (running) {
        menu();

        try {
            int command = mapCommand(getCommand());
            switch (command) {
                case 0:
                    // exit case
                    running = false;
                    break;
                default:
                    std::cout << "Invalid command.\n";
                    break;
            }
        }
        catch (...) {
            std::cout << "An exception occurred!\n";
        }
    }
}
