//
// Created by Emanuel on 03.12.2022.
//

#include "Polynomial.h"
#include "MultiplicationStrategy/Sequential/Simple/SequentialSimpleMultiplicationStrategy.h"

#include <random>
#include <iostream>

Polynomial::Polynomial(int degree) {
    coefficients.reserve(degree + 1);
    randomInit(degree);

    multiplyStrategy = SequentialSimpleMultiplicationStrategy::multiply;
}

Polynomial::Polynomial(std::vector<int> coefficients) : coefficients(std::move(coefficients)) {
    multiplyStrategy = SequentialSimpleMultiplicationStrategy::multiply;
}

void Polynomial::randomInit(int degree, int minCoefficient, int maxCoefficient) {
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(minCoefficient, maxCoefficient);

    for (int i = 0; i <= degree; ++i) {
        coefficients.push_back(distribution(gen));
    }
}

Polynomial Polynomial::operator*(const Polynomial &rhs) const {
    return multiplyStrategy(*this, rhs);
}

const Polynomial &Polynomial::setMultiplicationStrategy(std::function<Polynomial(const Polynomial&, const Polynomial&)> multiplyStrategy) {
    this->multiplyStrategy = std::move(multiplyStrategy);
    return *this;
}

int Polynomial::degree() const {
    return coefficients.size() - 1;
}

const int &Polynomial::operator[](int index) const {
    return coefficients[index];
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    for (int i = 0; i < p.coefficients.size(); ++i) {
        os << p.coefficients[i] << " * x^" << i;
        if (i != p.coefficients.size() - 1) {
            os << " + ";
        }
    }

    return os;
}
