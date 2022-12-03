//
// Created by Emanuel on 03.12.2022.
//

#ifndef ASSIGNMENT5_POLYNOMIAL_H
#define ASSIGNMENT5_POLYNOMIAL_H

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
    explicit Polynomial(int degree);

    explicit Polynomial(std::vector<int> coefficients);

    int degree() const;

    const Polynomial& setMultiplicationStrategy(std::function<Polynomial(const Polynomial&, const Polynomial&)> multiplyStrategy);

    Polynomial operator* (const Polynomial& rhs) const;

    const int& operator[] (int) const;

    friend std::ostream& operator<< (std::ostream& os, const Polynomial& p);
private:
    void randomInit(int degree, int minCoefficient=0, int maxCoefficient=500);
};


#endif //ASSIGNMENT5_POLYNOMIAL_H
