//
// Created by Emanuel on 22.10.2022.
//

#ifndef BANKACCOUNTS_ACCOUNTTRANSFEROPERATION_H
#define BANKACCOUNTS_ACCOUNTTRANSFEROPERATION_H



class AccountTransferOperation {
private:
    int sourceAccountId;
    int destinationAccountId;
    int amount;
public:
    AccountTransferOperation(int sourceAccountId, int destinationAccountId, int amount) :
        sourceAccountId(sourceAccountId), destinationAccountId(destinationAccountId), amount(amount) {}

    int getSourceAccountId() const;

    int getDestinationAccountId() const;

    int getAmount() const;
};


#endif //BANKACCOUNTS_ACCOUNTTRANSFEROPERATION_H
