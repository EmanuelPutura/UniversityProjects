//
// Created by Emanuel on 04.04.2021.
//

#ifndef CONSOLEUI_H
#define CONSOLEUI_H

#include <string>

class ConsoleUI {
private:
    std::string getCommand() const;
    std::string getUserData(const std::string& message) const;
    bool isPositiveInteger(const std::string& string) const;
    int mapCommand(const std::string& command) const;
public:
    void menu();
    void run();
};

#endif
