#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>

#include <mutex>
#include <thread>
#include <condition_variable>

const std::string inputFilePath = "../files/input.in";

class Exception : public std::exception {
private:
    std::string errorMessage;
public:
    explicit Exception(const std::string& errorMessage) : errorMessage (errorMessage) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

void readVectorFromLine(std::vector<int>& v, std::string line) {
    v.clear();

    int currentElement;
    std::istringstream stream (line);

    while (stream >> currentElement) {
        v.push_back(currentElement);
    }
}

void readInput(std::vector<int>& v1, std::vector<int>& v2) {
    std::ifstream fileIn(inputFilePath);
    if (!fileIn.is_open()) {
        throw Exception("Error: file path '" + inputFilePath + "' does not exist!");
    }

    std::string line;
    std::getline(fileIn, line);
    readVectorFromLine(v1, line);
    std::getline(fileIn, line);
    readVectorFromLine(v2, line);

    fileIn.close();

    if (v1.size() != v2.size()) {
        throw Exception("Error: The two vectors read from the input file are expected to have the same length");
    }
}

void producerWorker(std::mutex& mtx, std::condition_variable& conditionalVar, bool& isProducerDone, int& currentIndex,
        int& currentProduct, const std::vector<int>& v1, const std::vector<int>& v2) {

    while (true) {
        int localCurrentProduct = v1[currentIndex] * v2[currentIndex];

        std::unique_lock<std::mutex> lock (mtx);
        while (isProducerDone) {
            conditionalVar.wait(lock);
        }

        currentProduct = localCurrentProduct;
        std::cout << currentIndex << ". Producer updated the current product: " << currentProduct << ", index = " << currentIndex << '\n';

        isProducerDone = true;
        currentIndex++;

        conditionalVar.notify_all();

        if (currentIndex == v1.size()) {
            break;
        }
    }
}

void consumerWorker(std::mutex& mtx, std::condition_variable& conditionalVar, bool& isProducerDone, const int& currentIndex,
        const int& currentProduct, int& currentSum, const int& vectorsSize) {
    currentSum = 0;

    while (true) {
        std::unique_lock<std::mutex> lock (mtx);
        while (!isProducerDone) {
            conditionalVar.wait(lock);
        }

        currentSum += currentProduct;
        std::cout << currentIndex - 1 << ". Consumer updated the current sum: " << currentSum << " with the current product: " << currentProduct
            << ", index = " << currentIndex - 1 << "\n\n";

        isProducerDone = false;
        conditionalVar.notify_all();

        if (currentIndex == vectorsSize) {
            break;
        }
    }
}

int main() {
    std::vector<int> v1;
    std::vector<int> v2;

    readInput(v1, v2);

    int currentIndex = 0;
    int currentProduct = 0;
    int currentSum = 0;
    bool isProducerDone = false;

    std::mutex mtx;
    std::condition_variable conditionalVar;

    std::thread producer (producerWorker, std::ref(mtx), std::ref(conditionalVar), std::ref(isProducerDone),
          std::ref(currentIndex), std::ref(currentProduct), v1, v2);
    std::thread consumer (consumerWorker, std::ref(mtx), std::ref(conditionalVar), std::ref(isProducerDone),
          std::ref(currentIndex), std::ref(currentProduct), std::ref(currentSum), v1.size());

    producer.join();
    consumer.join();

    std::cout << "---> The scalar product of the two given vectors is " << currentSum << ".\n";

    return 0;
}
