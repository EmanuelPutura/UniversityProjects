//
// Created by Emanuel on 22.10.2022.
//

#include "Bank.h"

void Bank::readAccountFromFile(std::string accountsFilePath) {
    std::ifstream fin(accountsFilePath);
    Account account;

    while (fin >> account) {
        idToAccountMap[account.getId()] = account;
        idToAccountMap[account.getId()].addLog(AccountLogEntry(getOperationNextSerialNumber(), AccountTransferOperation(-1, account.getId(), account.getBalance())));
    }

    fin.close();
}

int Bank::getOperationNextSerialNumber() {
    std::unique_lock<std::mutex> _(serialNumberMutex);
    return operationNextSerialNumber++;
}

int Bank::getAccountsNumber() const {
    return idToAccountMap.size();
}

bool Bank::executeTransferOperation(const AccountTransferOperation &operation) {
    auto tuple = getAccountsFromOperation(operation);
    if (!std::get<0>(tuple)) {
        return false;
    }

    auto sourceAccount = std::get<1>(tuple);
    auto destinationAccount = std::get<2>(tuple);
    int amount = operation.getAmount();

    bool lockedDestination = false;

    // maintain an ordering for the mutexes locking
    if (destinationAccount.getId() < sourceAccount.getId()) {
        destinationAccount.lock();
        lockedDestination = true;
    }

    sourceAccount.lock();
    if (sourceAccount.getBalance() < amount) {
        sourceAccount.unlock();

        if (lockedDestination) {
            destinationAccount.unlock();
        }

        return false;
    }

    int transactionSerialNumber = getOperationNextSerialNumber();
    sourceAccount.updateBalance(sourceAccount.getBalance() - amount, AccountLogEntry(transactionSerialNumber, operation));
    if (!lockedDestination) {
        destinationAccount.lock();
    }

    sourceAccount.unlock();
    destinationAccount.updateBalance(destinationAccount.getBalance() + amount, AccountLogEntry(transactionSerialNumber, operation));
    destinationAccount.unlock();

    return true;
}

bool Bank::executeConsistencyCheck() const {
    for (const auto& entry : idToAccountMap) {
        auto currentAccount = entry.second;
        auto currentLogs = currentAccount.getLogs();
        int accountBalance = currentAccount.getBalance();

        for (const auto& log : currentLogs) {
            auto transferOperation = log.getTransferOperation();
            int sign = transferOperation.getSourceAccountId() == currentAccount.getId() ? 1 : -1;

            auto iterator = idToAccountMap.find(transferOperation.getDestinationAccountId());
            if (iterator == idToAccountMap.end()) {
                return false;
            }

            auto destinationAccount = (*iterator).second;
            auto destinationAccountLogs = destinationAccount.getLogs();

            if (destinationAccountLogs.find(AccountLogEntry(log.getSerialNumber())) == destinationAccountLogs.end()) {
                return false;
            }

            accountBalance += sign * transferOperation.getAmount();
        }

        if (accountBalance) {
            return false;
        }
    }

    return true;
}

std::tuple<bool, Account, Account> Bank::getAccountsFromOperation(const AccountTransferOperation& operation) const {
    auto iterator = idToAccountMap.find(operation.getSourceAccountId());
    if (iterator == idToAccountMap.end()) {
        return {false, Account(), Account()};
    }

    auto sourceAccount = (*iterator).second;
    iterator = idToAccountMap.find(operation.getDestinationAccountId());
    if (iterator == idToAccountMap.end()) {
        return {false, Account(), Account()};
    }

    auto destinationAccount = (*iterator).second;
    return {true, sourceAccount, destinationAccount};
}
