#pragma once
#include "../../../Polynomial.h"
class SequentialKaratsubaMultiplicationStrategy {
public:
    static Polynomial multiply(const Polynomial& lhs, const Polynomial& rhs);
};

