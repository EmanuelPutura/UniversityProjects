//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAMBEVERAGE_COFFEE_H
#define WRITTENEXAMBEVERAGE_COFFEE_H

#include "Beverage.h"

class Coffee : public Beverage {
public:
    Coffee();
    double price() override;
};


#endif //WRITTENEXAMBEVERAGE_COFFEE_H
