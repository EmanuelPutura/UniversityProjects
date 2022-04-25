//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAMBEVERAGE_BEVERAGEWITHMILK_H
#define WRITTENEXAMBEVERAGE_BEVERAGEWITHMILK_H

#include "Beverage.h"
#include <memory>

class BeverageWithMilk : public Beverage {
private:
    int milkCount;
    std::unique_ptr<Beverage> beverage;
public:
    explicit BeverageWithMilk(std::unique_ptr<Beverage> beverage, int milkCount = 0);

    double price() override;
    void print() override;

    ~BeverageWithMilk();
};


#endif //WRITTENEXAMBEVERAGE_BEVERAGEWITHMILK_H
