//
// Created by Emanuel on 21.03.2021.
//

#ifndef ADMINCONSOLEUI_H
#define ADMINCONSOLEUI_H

#include "../GenericConsoleUI/ConsoleUI.h"
#include "../../exceptions/ServiceException/ServiceException.h"

#include <iostream>
#include <map>
#include <string>

class AdminConsoleUI : public ConsoleUI {
private:
    void add();
    void update();
    void remove();
    void display() const;

    int mapCommand(const std::string& command) const;
public:
    AdminConsoleUI(CoatsService service) : ConsoleUI(service) {
        try {
            service.addDefault();
        }
        catch (const ServiceException& exception) {
            std::cout << exception.getMessage() << '\n';
        }
    }

    void menu() const override;
    int run() override;
};

#endif
