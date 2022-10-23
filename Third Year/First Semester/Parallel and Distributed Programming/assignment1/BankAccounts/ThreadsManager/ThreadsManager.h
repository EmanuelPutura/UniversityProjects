//
// Created by Emanuel on 22.10.2022.
//

#ifndef BANKACCOUNTS_THREADSMANAGER_H
#define BANKACCOUNTS_THREADSMANAGER_H

#include <iostream>
#include "../Bank/Bank.h"


class ThreadsManager {
private:
    static const int MIN_OPERATIONS_NUMBER = 1;
    static const int MAX_OPERATIONS_NUMBER = 50;

    static AccountTransferOperation generateAccountTransferOperation(const Bank& bank);
public:
    static void worker(Bank& bank);

    static void executeConsistencyCheckWithProbability(const Bank& bank, double probability = 0.001);
};


#endif //BANKACCOUNTS_THREADSMANAGER_H
