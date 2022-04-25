#include "UpdateFunctionCall.h"

UpdateFunctionCall::UpdateFunctionCall(IService &caller, const std::string &size, const std::string &colour, int price, const std::string &photograph, const std::string &new_size, const std::string &new_colour, int new_price, int new_quantity, const std::string &new_photograph) :
    IFunctionCall(caller), size(size), colour(colour), price(price), photograph(photograph), new_size(new_size), new_colour(new_colour), new_price(new_price), new_quantity(new_quantity), new_photograph(new_photograph) {
}

void UpdateFunctionCall::call() {
    caller.update(size, colour, price, photograph, new_size, new_colour, new_price, new_quantity, new_photograph, false);
}
