//
// Created by Emanuel on 20.06.2021.
//

#include <iostream>

#include "Vector.h"
#include "SmartPointer.h"

void function() {
    SmartPointer<int> i1 {new int {1}};
    SmartPointer<int> i2 {new int {2}};
    SmartPointer<int> i3 {new int {3}};
    Vector<SmartPointer<int>> v1{};

    v1.add(i1).add(i2).add(i3);
    for (auto e : v1)
        std::cout << *e << ", "; // 1, 2, 3

    SmartPointer<std::string> s1 {new std::string {"A"}};
    SmartPointer<std::string> s2 = s1;
    SmartPointer<std::string> s3 {new std::string {"C"}};

    Vector<SmartPointer<std::string>> v2{};
    v2.add(s2).add(s1);

    try {
        v2 = v2 - s2;

        std::cout << '\n';
        for (auto e : v2)
            std::cout << *e << ", ";
        std::cout << '\n';

        v2 = v2 - s3;
    }
    catch (std::exception& ex) {
        std::cout << ex.what(); // Element does not exist
    }
}

int main() {
    function();
    return 0;
}