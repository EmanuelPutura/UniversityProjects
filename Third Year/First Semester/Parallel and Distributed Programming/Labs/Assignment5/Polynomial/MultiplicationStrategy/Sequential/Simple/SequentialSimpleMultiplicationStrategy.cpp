//
// Created by Emanuel on 03.12.2022.
//

#include "SequentialSimpleMultiplicationStrategy.h"

#include <iostream>

Polynomial SequentialSimpleMultiplicationStrategy::multiply(const Polynomial & lhs, const Polynomial & rhs) {
    int lhsDegree = lhs.degree();
    int rhsDegree = rhs.degree();

    std::vector<int> resultCoefficients (lhsDegree + rhsDegree + 1, 0);
    for (int i = 0; i <= lhsDegree; ++i) {
        for (int j = 0; j <= rhsDegree; ++j) {
            resultCoefficients[i + j] += lhs[i] * rhs[j];
        }
    }

    return Polynomial(resultCoefficients);
}
