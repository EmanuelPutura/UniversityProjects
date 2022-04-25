#ifndef IFUNCTIONCALL_H
#define IFUNCTIONCALL_H

#include <business/IService.h>

class IFunctionCall {
protected:
    IService& caller;
public:
    IFunctionCall(IService& caller);

    virtual void call() = 0;
};

#endif // IFUNCTIONCALL_H
