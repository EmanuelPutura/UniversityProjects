#ifndef REMOVEFUNCTIONCALL_H
#define REMOVEFUNCTIONCALL_H

#include "IFunctionCall.h"

class RemoveFunctionCall : public IFunctionCall {
private:
    std::string size, colour, photograph;
    int price;
public:
    RemoveFunctionCall(IService& caller, const std::string& size, const std::string& colour, int price, const std::string& photograph);

    void call() override;
};

#endif // REMOVEFUNCTIONCALL_H
