//
// Created by Emanuel on 23.03.2021.
//

#ifndef USERCONSOLEUI_H
#define USERCONSOLEUI_H

#include "../GenericConsoleUI/ConsoleUI.h"

class UserConsoleUI : public ConsoleUI {
private:
    int mapCommand(const std::string& command) const;
    void trenchCoatMenu() const;
    void display();
    void add(const int& index, const std::string& size);
    void showShoppingBasket() const;
    void showShoppingBasketFile() const;
public:
    UserConsoleUI(CoatsService service) : ConsoleUI(service) {}

    void menu() const override;
    int run() override;
};

#endif
