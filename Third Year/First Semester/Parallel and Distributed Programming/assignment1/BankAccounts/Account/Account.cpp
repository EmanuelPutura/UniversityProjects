//
// Created by Emanuel on 22.10.2022.
//

#include "Account.h"


std::istream& operator>>(std::istream& is, Account& account) {
    is >> account.id >> account.balance;
    return is;
}

void Account::operator=(const Account& other) {
    id = other.id;
    balance = other.balance;
    logs = other.logs;
}

bool Account::operator==(const Account &other) const {
    return id == other.id;
}
