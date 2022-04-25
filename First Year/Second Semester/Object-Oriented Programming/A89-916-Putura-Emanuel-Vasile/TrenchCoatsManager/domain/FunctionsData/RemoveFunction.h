#ifndef REMOVEFUNCTION_H
#define REMOVEFUNCTION_H

#include "IFunctionCall.h"

class RemoveFunction : public IFunctionCall {
private:
    std::string size, colour, photograph;
    int price;
public:
    RemoveFunction(IService& caller, const std::string& size, const std::string& colour, int price, const std::string& photograph);

    void call() override;
};

#endif // REMOVEFUNCTION_H
