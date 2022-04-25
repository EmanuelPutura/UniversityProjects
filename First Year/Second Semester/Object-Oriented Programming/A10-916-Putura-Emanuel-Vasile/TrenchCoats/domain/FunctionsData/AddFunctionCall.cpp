#include "AddFunctionCall.h"

AddFunctionCall::AddFunctionCall(IService& caller, const std::string &size, const std::string &colour, int price, int quantity, const std::string &photograph) :
    IFunctionCall(caller), size(size), colour(colour), price(price), quantity(quantity), photograph(photograph) {
}

void AddFunctionCall::call() {
    caller.add(size, colour, price, quantity, photograph, false);
}
