#ifndef UPDATEFUNCTIONCALL_H
#define UPDATEFUNCTIONCALL_H

#include "IFunctionCall.h"

class UpdateFunctionCall : public IFunctionCall {
private:
    std::string size, colour, photograph;
    int price;
    std::string new_size, new_colour, new_photograph;
    int new_price, new_quantity;
public:
    UpdateFunctionCall(IService& caller, const std::string& size, const std::string& colour, int price, const std::string& photograph,
        const std::string& new_size, const std::string& new_colour, int new_price, int new_quantity, const std::string& new_photograph);

    virtual void call() override;
};

#endif // UPDATEFUNCTIONCALL_H
