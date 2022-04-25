#ifndef ADDFUNCTIONCALL_H
#define ADDFUNCTIONCALL_H

#include "IFunctionCall.h"

#include <string>

class AddFunctionCall : public IFunctionCall {
private:
    std::string size, colour, photograph;
    int price, quantity;
public:
    AddFunctionCall(IService& caller, const std::string& size, const std::string& colour, int price, int quantity, const std::string& photograph);

    void call() override;
};

#endif // ADDFUNCTIONCALL_H
