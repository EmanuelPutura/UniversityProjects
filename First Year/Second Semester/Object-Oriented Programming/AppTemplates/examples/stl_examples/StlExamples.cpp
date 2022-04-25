//
// Created by Emanuel on 04.04.2021.
//

#include "StlExamples.h"

#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>

void TestSTL::testShort() {
    std::vector<int> vector_ints;

    vector_ints.push_back(4);
    vector_ints.push_back(5);
    vector_ints.push_back(3);
    vector_ints.push_back(8);
    vector_ints.push_back(10);

    int index = 0;
    for (std::vector<int>::iterator it = vector_ints.begin(); it != vector_ints.end(); ++it) {
        std::cout << *it << ' ' << vector_ints[index] << '\n';
        index++;
    }
    std::cout << "-----------------------------------------------------\n";

    vector_ints[1] = 2;
    index = 0;
    for (std::vector<int>::iterator it = vector_ints.begin(); it != vector_ints.end(); ++it) {
        std::cout << *it << ' ' << vector_ints[index] << '\n';
        index++;
    }
    std::cout << "-----------------------------------------------------\n";

    std::cout << "Let's make some erases!\n";
    std::cout << vector_ints.size() << ' ' << vector_ints[1] << ' ' << vector_ints[2] << '\n';
    vector_ints.erase(vector_ints.begin() + 1);
    std::cout << vector_ints.size() << ' ' << vector_ints[1]  << '\n';
    vector_ints.push_back(3);
    std::cout << "-----------------------------------------------------\n";

    std::cout << "Now let's play a little with find()\n";
    std::cout << "Element 3 found on position: " << std::find(vector_ints.begin(), vector_ints.end(), 3) - vector_ints.begin() << '\n';
    std::cout << "-----------------------------------------------------\n";

    std::cout << "It's time for find_if()\n";
    std::cout << "Attempt to find element 3 position: ";
    std::cout << std::find_if(vector_ints.begin(), vector_ints.end(), [](const auto& element) { return element == 3; }) - vector_ints.begin();
    std::cout << "\n-----------------------------------------------------\n";

    std::cout << "Now let's print the elements, but in a cool way ;)\n";
    std::for_each(vector_ints.begin(), vector_ints.end(), [](const auto& element) { std::cout << element << ' '; });
    std::cout << "\n-----------------------------------------------------\n";

    std::cout << "Time for count_if(). Hurray!\n";
    std::cout << "The number of odd elements is: ";
    std::cout << std::count_if(vector_ints.begin(), vector_ints.end(), [](const auto& element) { return element % 2 == 1; });
    std::cout << "\n-----------------------------------------------------\n";

    std::cout << "Alert! Serious stuff is going on: copy_if()\n";
    std::cout << "Let's build a new vector that contains only the even numbers: ";
    std::vector<int> even_nos(3);
    std::copy_if(vector_ints.begin(), vector_ints.end(), even_nos.begin(), [](const auto& element) { return element % 2 == 0; });
    std::for_each(even_nos.begin(), even_nos.end(), [](const auto& element) { std::cout << element << ' '; });
    std::cout << "\n-----------------------------------------------------\n";
}

void TestSTL::testSTLAll() {
    testShort();
}
