//
// Created by Emanuel on 21.03.2021.
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
