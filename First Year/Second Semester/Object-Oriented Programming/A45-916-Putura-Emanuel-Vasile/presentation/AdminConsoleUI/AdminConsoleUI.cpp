//
// Created by Emanuel on 21.03.2021.
//

#include "AdminConsoleUI.h"
#include "../../exceptions/ServiceException/ServiceException.h"
#include "../../exceptions/ConsoleUIException/ConsoleUIException.h"

#include <iostream>

void AdminConsoleUI::menu() const {
    TextTable table {2};
    table.addHeader(2, "COMMAND", "COMMAND DESCRIPTION");
    table.addRow(2, "add", "add a new trench coat");
    table.addRow(2, "update", "update a trench coat");
    table.addRow(2, "remove", "remove a trench coat");
    table.addRow(2, "display", "display all trench coats in the repository");
    table.addRow(2, "switch", "switch to user mode");
    table.addRow(2, "exit", "exit the application");
    std::cout << "Admin Mode On\nApplication menu:\n" << table;
}

int AdminConsoleUI::run() {
    bool running = true;
    while (running) {
        menu();

        int command = mapCommand(getCommand());
        try {
            switch (command) {
                case 0:
                    // add case
                    add();
                    break;
                case 1:
                    // update case
                    update();
                    break;
                case 2:
                    // remove case
                    remove();
                    break;
                case 3:
                    // display case
                    display();
                    break;
                case 4:
                    return 1;
                case 5:
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

void AdminConsoleUI::add() {
    std::string size = getUserData("Please input the size of the trench coat:");
    std::string colour = getUserData("Please input the colour of the trench coat:");
    std::string price = getUserData("Please input the price of the trench coat:");
    std::string quantity = getUserData("Please input the trench coat's quantity:");
    std::string photograph = getUserData("Please input the link of a photograph of the trench coat:");

    if (!isPositiveInteger(price))
        throw ConsoleUIException("The price of the trench coat must be a positive integer.\n");
    if (!isPositiveInteger(quantity))
        throw ConsoleUIException("The trench coat's quantity must be a positive integer.\n");

    try {
        service.add(size, colour, stoi(price), stoi(quantity), photograph);
    }
    catch (const ServiceException& exception) {
        std::cout << "Operation add failed: " << exception.getMessage() << '\n';
    }
}

void AdminConsoleUI::update() {
    std::string size = getUserData("Please input the size of the trench coat:");
    std::string colour = getUserData("Please input the colour of the trench coat:");
    std::string price = getUserData("Please input the price of the trench coat:");
    std::string photograph = getUserData("Please input the link of a photograph of the trench coat:");
    std::string new_size = getUserData("Please input the new size of the trench coat:");
    std::string new_colour = getUserData("Please input the new colour of the trench coat:");
    std::string new_price = getUserData("Please input the new price of the trench coat:");
    std::string new_quantity = getUserData("Please input the trench coat's new quantity:");
    std::string new_photograph = getUserData("Please input the link of a new photograph for the trench coat:");

    if (!isPositiveInteger(price) || !isPositiveInteger(new_price))
        throw ConsoleUIException("The price of the trench coat must be a positive integer.\n");
    if (!isPositiveInteger(new_quantity))
        throw ConsoleUIException("The trench coat's quantity must be a positive integer.\n");

    try {
        service.update(size, colour, stoi(price), photograph, new_size, new_colour, stoi(new_price), stoi(new_quantity), new_photograph);
    }
    catch (const ServiceException& exception) {
        std::cout << "Operation update failed: " << exception.getMessage() << '\n';
    }
}

void AdminConsoleUI::remove() {
    std::string size = getUserData("Please input the size of the trench coat:");
    std::string colour = getUserData("Please input the colour of the trench coat:");
    std::string price = getUserData("Please input the price of the trench coat:");
    std::string photograph = getUserData("Please input the link of a photograph of the trench coat:");

    if (!isPositiveInteger(price))
        throw ConsoleUIException("The price of the trench coat must be a positive integer.\n");

    try {
        service.remove(size, colour, stoi(price), photograph);
    }
    catch (const ServiceException& exception) {
        std::cout << "Operation remove failed: " << exception.getMessage() << '\n';
    }
}

void AdminConsoleUI::display() const {
    service.getLength() ? std::cout << service.getDataTextTable(service.getData(), service.getLength()) << '\n' : std::cout << "No trench coats were found.\n";
}

int AdminConsoleUI::mapCommand(const std::string& command) const {
    std::string commands[] = {"add", "update", "remove", "display", "switch", "exit"};
    int int_commands[] = {0, 1, 2, 3, 4, 5};

    for (size_t i = 0; i < 6; ++i)
        if (command == commands[i]) return int_commands[i];
    return -1;
}
