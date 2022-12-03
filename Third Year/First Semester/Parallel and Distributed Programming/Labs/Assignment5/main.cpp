#include <iostream>
#include "Polynomial/Polynomial.h"

int main() {
    auto p1Coefficients = {5, 0, 10, 6};
    auto p2Coefficients = {1, 2, 4};

    Polynomial p1 (p1Coefficients);
    Polynomial p2 (p2Coefficients);
    std::cout << "P1 = " << p1 << '\n' << "P2 = " << p2 << '\n' << "P1 * P2 = " << p1 * p2;

    return 0;
}
