#pragma once

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>

#include "../../../Polynomial.h"

class ParallelizedSimpleMultiplicationStrategy {
public:
    static Polynomial multiply(const Polynomial& lhs, const Polynomial& rhs);
};
