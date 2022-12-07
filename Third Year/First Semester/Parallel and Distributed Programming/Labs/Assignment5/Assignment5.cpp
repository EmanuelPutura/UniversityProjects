#include <iostream>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <thread>

#include "Polynomial/Polynomial.h"
#include "Polynomial/MultiplicationStrategy/Parallelized/Simple/ParallelizedSimpleMultiplicationStrategy.h"
#include "Polynomial/MultiplicationStrategy/Sequential/Karatsuba/SequentialKaratsubaMultiplicationStrategy.h"
#include "Polynomial/MultiplicationStrategy/Parallelized/Karatsuba/ParallelizedKaratsubaMultiplicationStrategy.h"
#include "Polynomial/MultiplicationStrategy/Parallelized/Karatsuba/ParallelizedKaratsubaMultiplicationStrategy.h"

std::pair<Polynomial, Polynomial> setupPolynomial() {
    std::string command;
    std::cout << "Do you want to use the default polynomials? [Y/anything]\ncommand >> ";
    std::cin >> command;

    if (command == "Y") {
        auto p1Coefficients = { 5, 0, 10, 6 };
        auto p2Coefficients = { 1, 2, 4 };

        Polynomial p1(p1Coefficients);
        Polynomial p2(p2Coefficients);

        std::cout << "P1 = " << p1 << '\n' << "P2 = " << p2 << "\n\n";
        return { p1, p2 };
    }
    else {
        return { Polynomial(10000), Polynomial(10000) };
    }
}

void run(const Polynomial& p1, const Polynomial& p2, const std::string& method) {
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    std::cout << method;

    if (p1.degree() <= 15 && p2.degree() <= 15) {
        std::cout << ": P1 * P2 = " << p1 * p2 << '\n';
    }

    std::cout << '\n';

    std::chrono::system_clock::time_point stopTime = std::chrono::system_clock::now();
    std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count() << "us\n\n";
}

int main()
{
    auto polynomials = setupPolynomial();
    auto p1 = polynomials.first;
    auto p2 = polynomials.second;

    run(p1, p2, "Simple sequential multiplication");

    p1.setMultiplicationStrategy(ParallelizedSimpleMultiplicationStrategy::multiply);
    run(p1, p2, "Simple parallelized multiplication");

    p1.setMultiplicationStrategy(SequentialKaratsubaMultiplicationStrategy::multiply);
    run(p1, p2, "Karatsuba sequential multiplication");

    p1.setMultiplicationStrategy(ParallelizedKaratsubaMultiplicationStrategy::multiply);
    run(p1, p2, "Karatsuba parallelized multiplication");

    return 0;
}
