//
// Created by Emanuel on 23.03.2021.
//

#include "UserConsoleUI.h"
#include "../../exceptions/ServiceException/ServiceException.h"
#include "../../exceptions/ConsoleUIException/ConsoleUIException.h"

#include <iostream>

void UserConsoleUI::menu() const {
    TextTable table {2};
    table.addHeader(2, "COMMAND", "COMMAND DESCRIPTION");
    table.addRow(2, "display", "display the trench coats in the database, having a given size, one by one");
    table.addRow(2, "shopping basket", "see the shopping basket and the total price of the items");
    table.addRow(2, "switch", "switch to user mode");
    table.addRow(2, "exit", "exit the application");
    std::cout << "User Mode On\nApplication menu:\n" << table;
}

int UserConsoleUI::run() {
    bool running = true;
    while (running) {
        menu();

        int command = mapCommand(getCommand());
        try {
            switch (command) {
                case 0:
                    // display case
                    display();
                    break;
                case 1:
                    // shopping basket case
                    showShoppingBasket();
                    break;
                case 2:
                    // switch case
                    return 1;
                case 3:
                    // exit case
                    running = false;
                    break;
                default:
                    std::cout << "Invalid command.\n";
                    break;
            }
        }
        catch (const ConsoleUIException& exception) {
            std::cout << exception.getMessage();
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

int UserConsoleUI::mapCommand(const std::string &command) const {
    std::string commands[] = {"display", "shopping basket", "switch", "exit", "add", "!add", "stop"};
    int int_commands[] = {0, 1, 2, 3, 4, 5, 6};

    for (size_t i = 0; i < 7; ++i)
        if (command == commands[i]) return int_commands[i];
    return -1;
}

void UserConsoleUI::trenchCoatMenu() const {
    TextTable table {2};
    table.addHeader(2, "COMMAND", "COMMAND DESCRIPTION");
    table.addRow(2, "add", "choose to add the trench to the shopping basket");
    table.addRow(2, "!add", "choose not to add the trench coat to the basket and to continue to the next");
    table.addRow(2, "stop", "stop displaying trench coats");
    std::cout << "Trench Coat options:\n" << table << '\n';
}

void UserConsoleUI::display() {
    std::string size = getUserData("Please input the size of the trench coats:");

    int length = service.getCoatsPerSizeLength(size), i = 0;
    bool main_running = true;
    if (!length)
        throw ConsoleUIException("No trench coats were found.\n\n");

    while (main_running) {
        service.launchBrowserSizeCoatPhoto(i, size);
        std::cout << "Trench Coat:\n" << service.getSingleCoatPerSizeTextTable(i, size) << '\n';
        trenchCoatMenu();

        bool child_running = true;
        while (child_running) {
            int command = mapCommand(getCommand());
            switch (command) {
                case 4:
                    child_running = false;
                    add(i, size);
                    break;
                case 5:
                    child_running = false;
                    std::cout << "Trench coat was not added. You can continue searching for the one that best suits you.\n\n";
                    break;
                case 6:
                    main_running = child_running = false;
                    break;
                default:
                    std::cout << "Invalid command.\n";
                    break;
            }
        }
        length = service.getCoatsPerSizeLength(size);
        if (!length)
            throw ConsoleUIException("No trench coats were found.\n\n");
        (i >= length - 1) ? i = 0 : i++;
    }
}

void UserConsoleUI::add(const int& index, const std::string& size) {
    service.addToShoppingBasket(index, size);
    std::cout << "Trench coat added successfully to the cart.\nCurrent total payment: $" << service.getPayment() << "\n\n";
}

void UserConsoleUI::showShoppingBasket() const {
    auto table = service.getShoppingBasket();
    if (table.getRowsNo() == 1) std::cout << "Your shopping basket is empty.\n\n";
    else std::cout << "Your shopping basket is:\n" << table << "Total payment: $" << service.getPayment() << "\n\n";
}
