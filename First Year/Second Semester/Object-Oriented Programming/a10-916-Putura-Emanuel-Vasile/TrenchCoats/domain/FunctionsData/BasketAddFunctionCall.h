#ifndef BASKETADDFUNCTIONCALL_H
#define BASKETADDFUNCTIONCALL_H

#include "IFunctionCall.h"

class BasketAddFunctionCall : public IFunctionCall {
private:
    int index;
    std::string size;
public:
    BasketAddFunctionCall(IService& caller, int index, const std::string& size);

    void call() override;
};

#endif // BASKETADDFUNCTIONCALL_H
