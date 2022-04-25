#ifndef BASKETREMOVEFUNCTIONCALL_H
#define BASKETREMOVEFUNCTIONCALL_H

#include "IFunctionCall.h"

class BasketRemoveFunctionCall : public IFunctionCall {
private:
    TrenchCoat coat;
public:
    BasketRemoveFunctionCall(IService& caller, const TrenchCoat& coat);

    void call() override;
};

#endif // BASKETREMOVEFUNCTIONCALL_H
