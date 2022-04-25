//
// Created by Emanuel on 20.06.2021.
//

#include "BeverageMachine.h"
#include "Beverage.h"
#include "BeverageWithMilk.h"
#include "Tea.h"
#include "Coffee.h"

#include <memory>

void BeverageMachine::prepare(const std::string &beverageType, int milkCount) {
    if (beverageType == "Tea") {
        if (milkCount) {
            std::unique_ptr<Beverage> tea = std::make_unique<Tea>();
            BeverageWithMilk beverage {std::move(tea), milkCount};
            beverage.print();
            std::cout << ' ' << beverage.price() << '\n';
        }
        else {
            Tea beverage;
            beverage.print();
            std::cout << ' ' << beverage.price() << '\n';
        }
    }
    else if (beverageType == "Coffee") {
        if (milkCount) {
            std::unique_ptr<Beverage> coffee = std::make_unique<Coffee>();
            BeverageWithMilk beverage {std::move(coffee), milkCount};
            beverage.print();
            std::cout << ' ' << beverage.price() << '\n';
        }
        else {
            Coffee beverage;
            beverage.print();
            std::cout << ' ' << beverage.price() << '\n';
        }
    }
}
