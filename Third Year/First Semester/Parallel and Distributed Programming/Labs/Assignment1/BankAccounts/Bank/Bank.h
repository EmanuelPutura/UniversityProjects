//
// Created by Emanuel on 22.10.2022.
//

#ifndef BANKACCOUNTS_BANK_H
#define BANKACCOUNTS_BANK_H

#include <fstream>
#include <unordered_map>
#include <mutex>
#include <string>
#include "../Account/Account.h"


class Bank {
private:
    int operationNextSerialNumber;
    std::unordered_map<int, Account> idToAccountMap;
    mutable std::mutex serialNumberMutex;

    void readAccountFromFile(std::string accountsFilePath);

    std::tuple<bool, Account, Account> getAccountsFromOperation(const AccountTransferOperation& operation) const;
public:
    static const int MAX_BALANCE = std::numeric_limits<int>::max();

    Bank(std::string accountsFilePath) : operationNextSerialNumber(1) {
       readAccountFromFile(accountsFilePath);
    }

    bool executeTransferOperation(const AccountTransferOperation& operation);

    bool executeConsistencyCheck() const;

    int getOperationNextSerialNumber();

    int getAccountsNumber() const;
};


#endif //BANKACCOUNTS_BANK_H
