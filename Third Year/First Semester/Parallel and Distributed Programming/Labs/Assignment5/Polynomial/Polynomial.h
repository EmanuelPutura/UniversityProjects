#pragma once

#include <vector>
#include <limits>
#include <functional>
#include <ostream>

class Polynomial {
private:
    /*
     * This polynomial class accepts only integer coefficients.
     * Here, coefficients[i] = k <=> the coefficient of x^i is k
     */
    std::vector<int> coefficients;

    std::function<Polynomial(const Polynomial&, const Polynomial&)> multiplyStrategy;
public:
    Polynomial();

    explicit Polynomial(int degree);

    explicit Polynomial(std::vector<int> coefficients);

    int degree() const;

    const Polynomial& setMultiplicationStrategy(std::function<Polynomial(const Polynomial&, const Polynomial&)> multiplyStrategy);

    Polynomial getSubPolynomial(int startCoefficientIndex, int endCoefficientIndex) const;

    Polynomial operator+ (const Polynomial& rhs) const;

    Polynomial operator- (const Polynomial& rhs) const;

    Polynomial operator* (const Polynomial& rhs) const;

    Polynomial operator>> (int shift);

    const int& operator[] (int) const;

    friend std::ostream& operator<< (std::ostream& os, const Polynomial& p);
private:
    void randomInit(int degree, int minCoefficient = 0, int maxCoefficient = 500);
};
