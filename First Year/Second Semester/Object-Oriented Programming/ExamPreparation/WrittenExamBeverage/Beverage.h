//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAMBEVERAGE_BEVERAGE_H
#define WRITTENEXAMBEVERAGE_BEVERAGE_H

#include <string>
#include <iostream>

class Beverage {
private:
    std::string description;
public:
    Beverage(const std::string& description);
    virtual ~Beverage();

    virtual double price() = 0;
    virtual void print();

    inline const std::string& getDescription() const { return description; }
};


#endif //WRITTENEXAMBEVERAGE_BEVERAGE_H
