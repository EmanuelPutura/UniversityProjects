#include "Polynomial.h"

#include <random>
#include <iostream>
#include "MultiplicationStrategy/Sequential/Simple/SequentialSimpleMultiplicationStrategy.h"

Polynomial::Polynomial() {}

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

Polynomial Polynomial::operator+(const Polynomial& rhs) const {
    int minDegree = std::min(degree(), rhs.degree());
    int maxDegree = std::max(degree(), rhs.degree());
    
    std::vector<int> resultCoefficients(maxDegree + 1, 0);

    for (int i = 0; i <= minDegree; ++i) {
        resultCoefficients[i] = coefficients[i] + rhs[i];
    }

    if (maxDegree == degree()) {
        for (int i = minDegree + 1; i <= maxDegree; ++i) {
            resultCoefficients[i] = coefficients[i];
        }
    }
    else {
        for (int i = minDegree + 1; i <= maxDegree; ++i) {
            resultCoefficients[i] = rhs[i];
        }
    }

    int i = resultCoefficients.size() - 1;
    while (resultCoefficients[i] == 0 && i > 0) {
        resultCoefficients.pop_back();
        i--;
    }

    return Polynomial(resultCoefficients);
}

Polynomial Polynomial::operator-(const Polynomial& rhs) const {
    int minDegree = std::min(degree(), rhs.degree());
    int maxDegree = std::max(degree(), rhs.degree());

    std::vector<int> resultCoefficients(maxDegree + 1, 0);

    for (int i = 0; i <= minDegree; ++i) {
        resultCoefficients[i] = coefficients[i] - rhs[i];
    }

    if (maxDegree == degree()) {
        for (int i = minDegree + 1; i <= maxDegree; ++i) {
            resultCoefficients[i] = coefficients[i];
        }
    }
    else {
        for (int i = minDegree + 1; i <= maxDegree; ++i) {
            resultCoefficients[i] = -rhs[i];
        }
    }

    int i = resultCoefficients.size() - 1;
    while (resultCoefficients[i] == 0 && i > 0) {
        resultCoefficients.pop_back();
        i--;
    }

    return Polynomial(resultCoefficients);
}

Polynomial Polynomial::operator*(const Polynomial& rhs) const {
    return multiplyStrategy(*this, rhs);
}

Polynomial Polynomial::operator>>(int shift) {
    std::vector<int> newCoefficients(shift, 0);
    newCoefficients.insert(newCoefficients.end(), coefficients.begin(), coefficients.end());
    return Polynomial(newCoefficients);
}

const Polynomial& Polynomial::setMultiplicationStrategy(std::function<Polynomial(const Polynomial&, const Polynomial&)> multiplyStrategy) {
    this->multiplyStrategy = std::move(multiplyStrategy);
    return *this;
}

Polynomial Polynomial::getSubPolynomial(int startCoefficientIndex, int endCoefficientIndex) const {
    return Polynomial(std::vector<int>(coefficients.begin() + startCoefficientIndex, coefficients.begin() + endCoefficientIndex));
}

int Polynomial::degree() const {
    return coefficients.size() - 1;
}

const int& Polynomial::operator[](int index) const {
    return coefficients[index];
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.coefficients.size(); ++i) {
        os << p.coefficients[i] << " * x^" << i;
        if (i != p.coefficients.size() - 1) {
            os << " + ";
        }
    }

    return os;
}
