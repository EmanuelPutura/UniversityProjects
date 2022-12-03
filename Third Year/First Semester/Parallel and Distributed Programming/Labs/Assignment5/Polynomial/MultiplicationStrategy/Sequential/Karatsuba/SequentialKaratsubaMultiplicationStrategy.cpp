#include "SequentialKaratsubaMultiplicationStrategy.h"
#include "../Simple/SequentialSimpleMultiplicationStrategy.h"

Polynomial SequentialKaratsubaMultiplicationStrategy::multiply(const Polynomial& lhs, const Polynomial& rhs) {
    if (lhs.degree() < 2 || rhs.degree() < 2) {
        return SequentialSimpleMultiplicationStrategy::multiply(lhs, rhs);
    }

    auto len = std::max(lhs.degree(), rhs.degree()) / 2;

    auto lhsLow = lhs.getSubPolynomial(0, len);
    auto lhsHigh = lhs.getSubPolynomial(len, lhs.degree() + 1);
    auto rhsLow = rhs.getSubPolynomial(0, len);
    auto rhsHigh = rhs.getSubPolynomial(len, rhs.degree() + 1);

    auto z1 = multiply(lhsLow, rhsLow);
    auto z2 = multiply(lhsLow + lhsHigh, rhsLow + rhsHigh);
    auto z3 = multiply(lhsHigh, rhsHigh);

    auto r1 = z3 >> 2 * len;
    auto r2 = ((z2 - z3) - z1) >> len;
    return (r1 + r2) + z1;
}
