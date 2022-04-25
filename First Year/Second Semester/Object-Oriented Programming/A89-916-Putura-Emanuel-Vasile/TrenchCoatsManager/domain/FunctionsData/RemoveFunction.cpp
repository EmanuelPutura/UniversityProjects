#include "RemoveFunction.h"

RemoveFunction::RemoveFunction(IService &caller, const std::string &size, const std::string &colour, int price, const std::string &photograph) :
        IFunctionCall(caller), size(size), colour(colour), price(price), photograph(photograph) {
}

void RemoveFunction::call() {
    caller.remove(size, colour, price, photograph);
}
