//
// Created by Emanuel on 22.10.2022.
//

#ifndef BANKACCOUNTS_ACCOUNT_H
#define BANKACCOUNTS_ACCOUNT_H

#include <iostream>
#include <unordered_set>
#include <mutex>
#include "../AccountLogEntry/AccountLogEntry.h"


class Account {
private:
    int id;
    int balance;
    std::unordered_set<AccountLogEntry, AccountLogEntryHashFunction> logs;

    mutable std::mutex accountMutex;
public:
    Account() : id(-1) {}

    Account(int id) : id(id), balance(0) {}

    Account(int id, int balance) : id(id), balance(balance) {}

    Account(const Account& other) {
        *this = other;
    }

    void operator=(const Account& other);

    bool operator==(const Account& other) const;

    friend std::istream& operator>>(std::istream& is, Account& account);

    int getId() const {
        return id;
    }

    int getBalance() const {
        return balance;
    }

    const std::unordered_set<AccountLogEntry, AccountLogEntryHashFunction>& getLogs() const {
        return logs;
    }

    void addLog(const AccountLogEntry& log) {
        logs.insert(log);
    }

    void updateBalance(int newBalance, const AccountLogEntry& entry) {
        balance = newBalance;
        logs.insert(entry);
    }

    inline void lock() const {
        accountMutex.lock();
    }

    inline void unlock() const {
        accountMutex.unlock();
    }
};


#endif //BANKACCOUNTS_ACCOUNT_H
