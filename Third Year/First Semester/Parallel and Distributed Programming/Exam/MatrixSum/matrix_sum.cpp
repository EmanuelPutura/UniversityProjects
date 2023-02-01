/*
* Problem statement: check the README
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <random>
#include <future>
#include <chrono>
#include <thread>
#include <mpi.h>

std::vector<std::vector<int>> generateRandomMatrix(int n);

int computeMatrixSum(const std::vector<std::vector<int>>& matrix);
int recursiveSum(const std::vector<std::vector<int>>& matrix, int firstLine, int lastLine, int threadsNo);

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "First argument must be the matrix dimension N (matrix is N x N), second argument must be the threads number!\n";
        return -1;
    }

    int n = atoi(argv[1]);
    int threadsNumber = atoi(argv[2]);

    auto matrix = generateRandomMatrix(n);
    auto realSum = computeMatrixSum(matrix);

    std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
    auto computedSum = recursiveSum(matrix, 0, n - 1, threadsNumber);
    std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

    std::cout << "Computed sum is " << computedSum << ", real sum is " << realSum << "\n";
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - beginTime).count() << '\n';

    return 0;
}

std::vector<std::vector<int>> generateRandomMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 99);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = dist(rng);
        }
    }

    return matrix;
}

int computeMatrixSum(const std::vector<std::vector<int>>& matrix) {
    int sum = 0;
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

int recursiveSum(const std::vector<std::vector<int>>& matrix, int firstLine, int lastLine, int threadsNo) {
    int sum = 0;

    if (firstLine == lastLine) {    
        for (int j = 0; j < matrix.size(); ++j) {
            sum += matrix[firstLine][j];
        }

        return sum;
    }

    int midPoint = (firstLine + lastLine) / 2;
    if (threadsNo <= 1) {
        return recursiveSum(matrix, firstLine, midPoint, 1) + recursiveSum(matrix, midPoint + 1, lastLine, 1);
    }

    std::future<int> firstHalfRes = std::async(std::launch::async, &recursiveSum, matrix, firstLine, midPoint, threadsNo / 2);
    int secondHalfResult = recursiveSum(matrix, midPoint + 1, lastLine, threadsNo / 2);
    return firstHalfRes.get() + secondHalfResult;
}
