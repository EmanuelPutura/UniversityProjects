//
// Created by Emanuel on 22.10.2022.
//

#ifndef BANKACCOUNTS_ACCOUNTLOGENTRY_H
#define BANKACCOUNTS_ACCOUNTLOGENTRY_H

#include <cstddef>
#include "../AccountOperation/AccountTransferOperation.h"


class AccountLogEntry {
private:
    int serialNumber;
    AccountTransferOperation operation;
public:
    AccountLogEntry(int serialNumber) : serialNumber(serialNumber), operation(AccountTransferOperation(-1, -1, 0)) {}

    AccountLogEntry(int serialNumber, AccountTransferOperation operation) : serialNumber(serialNumber), operation(operation) {}

    bool operator== (const AccountLogEntry& other) const;

    int getSerialNumber() const {
        return serialNumber;
    }

    const AccountTransferOperation& getTransferOperation() const {
        return operation;
    }
};


struct AccountLogEntryHashFunction {
    size_t operator()(const AccountLogEntry& logEntry) const {
        return logEntry.getSerialNumber();
    }
};


#endif //BANKACCOUNTS_ACCOUNTLOGENTRY_H
