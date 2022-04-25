//
// Created by Emanuel on 21.03.2021.
//

#include "TrenchCoat.h"

#include <iostream>

std::ostream &operator<<(std::ostream &os, const TrenchCoat& coat) {
    os << coat.size << ' ' << coat.colour << ' ' << coat.price << ' ' << coat.quantity << ' ' << coat.photograph;
    return os;
}

std::istream &operator>>(std::istream &is, TrenchCoat& coat) {
    is >> coat.size >> coat.colour >> coat.price >> coat.quantity >> coat.photograph;
    return is;
}

bool operator==(const TrenchCoat &t1, const TrenchCoat &t2) {
    return t1.size == t2.size && t1.colour == t2.colour && t1.price == t2.price && t1.photograph == t2.photograph;
}
