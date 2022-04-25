#include "BasketRemoveFunctionCall.h"

BasketRemoveFunctionCall::BasketRemoveFunctionCall(IService &caller, const TrenchCoat &coat) : IFunctionCall(caller), coat(coat) {
}

void BasketRemoveFunctionCall::call() {
    caller.removeFromShoppingBasket(coat, false);
}
