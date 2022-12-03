#pragma once
#include "../../../Polynomial.h"

class SequentialSimpleMultiplicationStrategy {
public:
    static Polynomial multiply(const Polynomial& lhs, const Polynomial& rhs);
};
