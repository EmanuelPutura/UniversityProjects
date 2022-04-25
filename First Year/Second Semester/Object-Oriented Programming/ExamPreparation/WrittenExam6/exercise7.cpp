//
// Created by Emanuel on 21.06.2021.
//

#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <cassert>

using namespace std;

template <class T>
T fct(vector<T>& v) {
    if (v.size() == 0)
        throw std::exception();

    T max = v[0];
    for (const auto& el : v)
        if (el > max) max = el;
    return max;
}

void testFunc() {
    vector<int> v1 {4, 2, 1, 6, 3, -4};
    assert(fct<int>(v1) == 6);
    vector<int> v2;

    try {
        fct<int>(v2);
        assert(false);
    }
    catch (std::exception&) {
        assert(true);
    }

    vector<double> v3 {2, 10.5, 6.33, -100, 9, 1.212};
    assert(fct<double>(v3) == 10.5);

    vector<string> v4 {"y", "q", "a", "m"};
    assert(fct<string>(v4) == "y");
}

int main() {
    testFunc();
    return 0;
}
