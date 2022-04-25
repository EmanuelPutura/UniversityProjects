#include "BasketAddFunctionCall.h"

BasketAddFunctionCall::BasketAddFunctionCall(IService &caller, int index, const std::string &size) : IFunctionCall(caller), index(index), size(size) {
}

void BasketAddFunctionCall::call() {
    caller.addToShoppingBasket(index, size, false);
}
