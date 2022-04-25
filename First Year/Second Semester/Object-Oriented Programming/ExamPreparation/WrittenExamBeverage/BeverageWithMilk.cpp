//
// Created by Emanuel on 20.06.2021.
//

#include "BeverageWithMilk.h"

BeverageWithMilk::BeverageWithMilk(std::unique_ptr<Beverage> beverage, int milkCount) : Beverage(beverage->getDescription()), beverage(std::move(beverage)), milkCount(milkCount) {
}

double BeverageWithMilk::price() {
    return beverage->price() + (double)milkCount * 0.5;
}

void BeverageWithMilk::print() {
    beverage->print();
    std::cout << ' ' << milkCount;
}

BeverageWithMilk::~BeverageWithMilk() {
}
