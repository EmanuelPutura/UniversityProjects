/*
* Problem statement: check the README
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <random>
#include <future>
#include <chrono>
#include <thread>

std::vector<int> generateVector(int n);

int computeScalarProductIterative(const std::vector<int>& v1, const std::vector<int>& v2);
int computeScalarProductRecursively(const std::vector<int>& v1, const std::vector<int>& v2, int left, int right, int threadsNo);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "First argument must be the vectors dimension N, second argument must be the threads number!\n";
        return -1;
    }

    int n = atoi(argv[1]);
    int threadsNumber = atoi(argv[2]);

    auto v1 = generateVector(n);
    auto v2 = generateVector(n);

    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    auto computedResult = computeScalarProductRecursively(v1, v2, 0, n - 1, threadsNumber);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    int realResult = computeScalarProductIterative(v1, v2);

    std::cout << "Computed scalar product is " << computedResult<< ", real result is " << realResult << "\n";
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count() << '\n';

    return 0;
}

std::vector<int> generateVector(int n) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99);

    std::vector<int> result(n);
    for (int i = 0; i < n; ++i) {
        result[i] = dist(rng);
    }

    return result;
}

int computeScalarProductIterative(const std::vector<int>& v1, const std::vector<int>& v2) {
    int result = 0;
    if (v1.size() != v2.size()) {
        return -1; // assume the scalar product is always positive, given the way the vectors are generated
    }

    for (int i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }

    return result;
}

int computeScalarProductRecursively(const std::vector<int>& v1, const std::vector<int>& v2, int left, int right, int threadsNo) {
    if (left == right) {
        return v1[left] * v2[right];
    }

    int mid = (left + right) / 2;
    if (threadsNo <= 1) {
        return computeScalarProductRecursively(v1, v2, left, mid, 1) + computeScalarProductRecursively(v1, v2, mid + 1, right, 1);
    }

    std::future<int> firstHalfFuture = std::async(std::launch::async, &computeScalarProductRecursively, v1, v2, left, mid, threadsNo / 2);
    int secondHalfResult = computeScalarProductRecursively(v1, v2, mid + 1, right, threadsNo / 2);

    return firstHalfFuture.get() + secondHalfResult;
}
