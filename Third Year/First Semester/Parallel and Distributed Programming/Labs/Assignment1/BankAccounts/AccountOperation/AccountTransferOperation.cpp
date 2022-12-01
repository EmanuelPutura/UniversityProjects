//
// Created by Emanuel on 22.10.2022.
//

#include "AccountTransferOperation.h"

int AccountTransferOperation::getSourceAccountId() const {
    return sourceAccountId;
}

int AccountTransferOperation::getAmount() const {
    return amount;
}

int AccountTransferOperation::getDestinationAccountId() const {
    return destinationAccountId;
}
