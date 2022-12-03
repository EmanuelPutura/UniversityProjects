#pragma once
#include "../../../Polynomial.h"

class ParallelizedKaratsubaMultiplicationStrategy {
private:
    static int MAX_DEPTH;
public:
    static Polynomial multiply(const Polynomial& lhs, const Polynomial& rhs);
private:
    static Polynomial multiplyImpl(const Polynomial& lhs, const Polynomial& rhs, int depth);
};
