//
// Created by Emanuel on 22.10.2022.
//

#include <vector>
#include "ThreadsManager.h"
#include "../RandomGenerator/RandomGenerator.h"


void ThreadsManager::worker(Bank& bank) {
    int operationsNumber = RandomGenerator::generateRandomIntBetween(MIN_OPERATIONS_NUMBER, MAX_OPERATIONS_NUMBER);
    std::vector<AccountTransferOperation> operations;
    operations.reserve(operationsNumber);

    for (int i = 0; i < operationsNumber; ++i) {
        operations[i] = generateAccountTransferOperation(bank);
    }

    for (int i = 0; i < operationsNumber; ++i) {
        executeConsistencyCheckWithProbability(bank);
        bank.executeTransferOperation(operations[i]);
    }
}

AccountTransferOperation ThreadsManager::generateAccountTransferOperation(const Bank &bank) {
    int accountMinId = 1, accountMaxId = bank.getAccountsNumber();
    int sourceAccountId = RandomGenerator::generateRandomIntBetween(accountMinId, accountMaxId);
    int destinationAccountId = sourceAccountId;

    while (sourceAccountId == destinationAccountId) {
        destinationAccountId = RandomGenerator::generateRandomIntBetween(accountMinId, accountMaxId);
    }

    int balance = RandomGenerator::generateRandomIntBetween(0, Bank::MAX_BALANCE);
    return AccountTransferOperation(sourceAccountId, destinationAccountId, balance);
}

void ThreadsManager::executeConsistencyCheckWithProbability(const Bank &bank, double probability) {
    double random01 = ((double) rand() / (RAND_MAX));
    if (random01 && random01 <= probability) {
        bool isValid = bank.executeConsistencyCheck();
        std::string validityMessage = isValid ? "is VALID.\n" : "is NOT VALID.\n";

        std::cout << "--- Executed a consistency check, result is that the state of the bank " + validityMessage;
    }
}
