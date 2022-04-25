//
// Created by Emanuel on 20.06.2021.
//

#include "Beverage.h"

Beverage::Beverage(const std::string &description) : description(description) {
}

void Beverage::print() {
    std::cout << description << ", " << price();
}

Beverage::~Beverage() {
}
