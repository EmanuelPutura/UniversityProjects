#include "ParallelizedSimpleMultiplicationStrategy.h"
#include "../../../../Utils/ThreadUtils.h"

#include <iostream>

Polynomial ParallelizedSimpleMultiplicationStrategy::multiply(const Polynomial& lhs, const Polynomial& rhs) {
    std::vector<int> resultCoefficients (lhs.degree() + rhs.degree() + 1, 0);

    for (int exponent = 0; exponent <= lhs.degree() + rhs.degree(); ++exponent) {
        boost::asio::post(ThreadUtils::getThreadPool(), [&lhs, &rhs, &resultCoefficients, exponent]() {
            for (int lhsExponent = std::max(0, exponent - rhs.degree()); lhsExponent <= lhs.degree() && lhsExponent <= exponent && exponent - lhsExponent <= rhs.degree(); ++lhsExponent) {
                int rhsExponent = exponent - lhsExponent;
                resultCoefficients[exponent] += lhs[lhsExponent] * rhs[rhsExponent];
            }
        });
    }

    ThreadUtils::getThreadPool().join();
    return Polynomial(resultCoefficients);
}
