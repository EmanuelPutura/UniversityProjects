//
// Created by Emanuel on 21.03.2021.
//

#include "CoatValidator.h"

bool CoatValidator::validate(const TrenchCoat& coat) {
    errors = "";
    if (coat.getSize() == "") errors += "Invalid trench coat size.\n";
    if (coat.getColour() == "") errors += "Invalid trench coat colour.\n";
    if (coat.getPrice() <= 0) errors += "Invalid trench coat price.\n";
    if (coat.getQuantity() <= 0) errors += "Invalid trench coat quantity.\n";
    if (coat.getPhotograph() == "") errors += "Invalid trench coat photograph.\n";
    return errors == "";
}
