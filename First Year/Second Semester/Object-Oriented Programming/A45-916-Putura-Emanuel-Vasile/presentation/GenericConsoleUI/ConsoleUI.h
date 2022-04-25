//
// Created by Emanuel on 21.03.2021.
//

#ifndef GENERICCONSOLEUI_H
#define GENERICCONSOLEUI_H

#include "../../business/CoatsService.h"

class ConsoleUI {
protected:
    CoatsService& service;

    std::string getCommand() const;
    std::string getUserData(const std::string& message) const;
    bool isPositiveInteger(const std::string& string) const;
public:
    explicit ConsoleUI(CoatsService& service) : service(service) {}

    virtual void menu() const = 0;
    virtual int run() = 0;
};

#endif
