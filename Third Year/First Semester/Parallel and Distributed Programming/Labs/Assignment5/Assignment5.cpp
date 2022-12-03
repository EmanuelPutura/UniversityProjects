#include <iostream>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <thread>

#include "Polynomial/Polynomial.h"
#include "Polynomial/MultiplicationStrategy/Parallelized/Simple/ParallelizedSimpleMultiplicationStrategy.h"
#include "Polynomial/MultiplicationStrategy/Sequential/Karatsuba/SequentialKaratsubaMultiplicationStrategy.h"
#include "Polynomial/MultiplicationStrategy/Parallelized/Karatsuba/ParallelizedKaratsubaMultiplicationStrategy.h"
#include "Polynomial/MultiplicationStrategy/Parallelized/Karatsuba/ParallelizedKaratsubaMultiplicationStrategy.h"

int main()
{
    auto p1Coefficients = { 5, 0, 10, 6 };
    auto p2Coefficients = { 1, 2, 4 };

    Polynomial p1(p1Coefficients);
    Polynomial p2(p2Coefficients);
    std::cout << "P1 = " << p1 << '\n' << "P2 = " << p2 << '\n';

    std::cout << "Simple sequential multiplication: P1 * P2 = " << p1 * p2 << '\n';

    p1.setMultiplicationStrategy(ParallelizedSimpleMultiplicationStrategy::multiply);
    std::cout << "Simple parallelized multiplication: P1 * P2 = " << p1 * p2 << '\n';

    p1.setMultiplicationStrategy(SequentialKaratsubaMultiplicationStrategy::multiply);
    std::cout << "Karatsuba sequential multiplication: P1 * P2 = " << p1 * p2 << '\n';

    p1.setMultiplicationStrategy(ParallelizedKaratsubaMultiplicationStrategy::multiply);
    std::cout << "Karatsuba parallelized multiplication: P1 * P2 = " << p1 * p2 << '\n';

    return 0;
}
