//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAMBEVERAGE_TEA_H
#define WRITTENEXAMBEVERAGE_TEA_H

#include "Beverage.h"

class Tea : public Beverage {
public:
    Tea();
    double price() override;
};


#endif //WRITTENEXAMBEVERAGE_TEA_H
