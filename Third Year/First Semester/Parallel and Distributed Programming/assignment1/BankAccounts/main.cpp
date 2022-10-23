#include <iostream>
#include <vector>
#include <thread>

#include "ThreadsManager/ThreadsManager.h"


int main(int argc, char** argv) {
    srand(time(0));

    const int DEFAULT_THREADS_NUMBER = 100;
    int threadsNumber = argc >= 2 ? atoi(argv[1]) : DEFAULT_THREADS_NUMBER;

    Bank bank("../Files/accounts.txt");

    std::vector<std::thread> threads;
    threads.reserve(threadsNumber);

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    for (size_t i = 0; i < threadsNumber; ++i) {
        threads.emplace_back(std::thread(ThreadsManager::worker, std::ref(bank)));
    }

    for (size_t i = 0; i < threadsNumber; ++i) {
        threads[i].join();
    }

    ThreadsManager::executeConsistencyCheckWithProbability(bank, 1);

    std::chrono::system_clock::time_point stopTime = std::chrono::system_clock::now();
    std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::microseconds>(stopTime-startTime).count() << "us\n";

    return 0;
}
