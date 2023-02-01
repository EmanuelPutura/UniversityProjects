/*
* Problem statement: check the README
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <mpi.h>

bool isPrime(int n);

std::vector<int> computePrimesUpToSqrt(int n);
std::vector<int> computePrimesAfterSqrt(const std::vector<int>& primes, int left, int right);

std::unordered_set<int> computeAllPrimesFromSqrt(int n);
bool validateFinalResult(int n, const std::vector<int> finalResult);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "First argument must be N!\n";
        return -1;
    }

    int n = atoi(argv[1]);
    int me, nrProcs;

    MPI_Init(0, 0);
    MPI_Comm_size(MPI_COMM_WORLD, &nrProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    std::vector<int> primes;
    if (me == 0) {
        primes = computePrimesUpToSqrt(n);
        auto primesSize = primes.size();
        
        // broadcast the size of the vector
        MPI_Bcast(&primesSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // broadcast the vector
        MPI_Bcast(primes.data(), primesSize, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else {
        int primesSize = 0;

        // get the broadcasted vector size
        MPI_Bcast(&primesSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        primes.resize(primesSize);

        // get the broadcasted vector
        MPI_Bcast(primes.data(), primesSize, MPI_INT, 0, MPI_COMM_WORLD);
    }

    int sqrtLimit = sqrt(n) + 1;
    int numbersPerProcess = (n - sqrt(n)) / nrProcs;

    int left = sqrtLimit + me * numbersPerProcess;
    int nextLeft = sqrtLimit + (me + 1) * numbersPerProcess;
    int right = me == (nrProcs - 1) ? n : nextLeft - 1;

    auto res = computePrimesAfterSqrt(primes, left, right);

    if (me == 0) {
        std::unordered_map<int, std::vector<int>> processToResult;
        for (const auto& el : res) {
            processToResult[0].push_back(el);
        }

        for (int p = 1; p < nrProcs; ++p) {
            MPI_Status status;
            int resSize;

            MPI_Recv(&resSize, 1, MPI_INT, p, 1, MPI_COMM_WORLD, &status);
            processToResult[p].resize(resSize);
            MPI_Recv(processToResult[p].data(), resSize, MPI_INT, p, 1, MPI_COMM_WORLD, &status);
        }

        std::cout << "...parent received data from all children processes\n";

        std::vector<int> finalResult;
        for (int p = 0; p < nrProcs; ++p) {
            std::cout << "Result computed by process " << p << ": ";
            auto& res = processToResult[p];

            for (const auto& el : res) {
                std::cout << el << ' ';
                finalResult.push_back(el);
            }

            std::cout << '\n';
        }

        auto validation = validateFinalResult(n, finalResult);
        std::cout << "\nResult of final validation: " << validation << '\n';
    }
    else {
        int resSize = res.size();
        MPI_Ssend(&resSize, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        MPI_Ssend(res.data(), resSize, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }

    std::cout << "...process " << me << " done\n";
    MPI_Finalize();

    return 0;
}

bool isPrime(int n) {
    if (n < 2) {
        return false;
    }

    if (n == 2) {
        return true;
    }

    if (n % 2 == 0) {
        return false;
    }

    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }

    return true;
}

std::vector<int> computePrimesUpToSqrt(int n) {
    if (n < 4) {
        return {};
    }

    std::vector<int> primes = { 2 };
    for (int d = 3; d * d <= n; d += 2) {
        if (isPrime(d)) {
            primes.push_back(d);
        }
    }
    
    return primes;
}

std::vector<int> computePrimesAfterSqrt(const std::vector<int>& primes, int left, int right) {
    std::vector<int> result;
    
    for (int no = left; no <= right; ++no) {
        bool prime = true;
        for (const auto& p : primes) {
            if (no % p == 0) {
                prime = false;
                break;
            }
        }

        if (prime) {
            result.push_back(no);
        }
    }

    return result;
}

std::unordered_set<int> computeAllPrimesFromSqrt(int n) {
    std::unordered_set<int> result;

    for (int i = sqrt(n) + 1; i <= n; ++i) {
        if (isPrime(i)) {
            result.insert(i);
        }
    }

    return result;
}

bool validateFinalResult(int n, const std::vector<int> finalResult) {
    auto trueResult = computeAllPrimesFromSqrt(n);    
    if (trueResult.size() != finalResult.size()) {
        return false;
    }

    for (const auto& el : finalResult) {
        if (trueResult.find(el) == trueResult.end()) {
            return false;
        }
    }

    return true;
}