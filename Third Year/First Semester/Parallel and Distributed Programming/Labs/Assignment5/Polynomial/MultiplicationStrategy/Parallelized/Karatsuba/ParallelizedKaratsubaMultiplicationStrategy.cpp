#include "ParallelizedKaratsubaMultiplicationStrategy.h"
#include "../../Sequential/Simple/SequentialSimpleMultiplicationStrategy.h"

#include <thread>
#include <iostream>
#include <future>

int ParallelizedKaratsubaMultiplicationStrategy::MAX_DEPTH = 4;

Polynomial ParallelizedKaratsubaMultiplicationStrategy::multiply(const Polynomial& lhs, const Polynomial& rhs) {
    return multiplyImpl(lhs, rhs, 0);
}

Polynomial ParallelizedKaratsubaMultiplicationStrategy::multiplyImpl(const Polynomial& lhs, const Polynomial& rhs, int depth) {
    if (depth >= MAX_DEPTH) {
        return SequentialSimpleMultiplicationStrategy::multiply(lhs, rhs);
    }

    if (lhs.degree() < 2 || rhs.degree() < 2) {
        return SequentialSimpleMultiplicationStrategy::multiply(lhs, rhs);
    }

    auto len = std::max(lhs.degree(), rhs.degree()) / 2;

    auto lhsLow = lhs.getSubPolynomial(0, len);
    auto lhsHigh = lhs.getSubPolynomial(len, lhs.degree() + 1);
    auto rhsLow = rhs.getSubPolynomial(0, len);
    auto rhsHigh = rhs.getSubPolynomial(len, rhs.degree() + 1);

    std::promise<Polynomial> promiseZ1;
    auto futureZ1 = promiseZ1.get_future();

    std::promise<Polynomial> promiseZ2;
    auto futureZ2 = promiseZ2.get_future();

    std::promise<Polynomial> promiseZ3;
    auto futureZ3 = promiseZ3.get_future();

    std::thread tZ1([&lhsLow, &rhsLow](std::promise<Polynomial>&& promise) {
        promise.set_value(multiply(lhsLow, rhsLow));
    }, std::move(promiseZ1));

    std::thread tZ2([&lhsLow, &lhsHigh, &rhsLow, &rhsHigh](std::promise<Polynomial>&& promise) {
        promise.set_value(multiply(lhsLow + lhsHigh, rhsLow + rhsHigh));
    }, std::move(promiseZ2));

    std::thread tZ3([&lhsHigh, &rhsHigh](std::promise<Polynomial>&& promise) {
        promise.set_value(multiply(lhsHigh, rhsHigh));
    }, std::move(promiseZ3));

    tZ1.join();
    tZ2.join();
    tZ3.join();

    auto z1 = futureZ1.get();
    auto z2 = futureZ2.get();
    auto z3 = futureZ3.get();
    
    auto r1 = z3 >> 2 * len;
    auto r2 = ((z2 - z3) - z1) >> len;
    return (r1 + r2) + z1;
}
