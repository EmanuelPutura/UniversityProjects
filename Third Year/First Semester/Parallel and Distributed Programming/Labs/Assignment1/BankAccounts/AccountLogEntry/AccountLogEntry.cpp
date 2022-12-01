//
// Created by Emanuel on 22.10.2022.
//

#include "AccountLogEntry.h"

bool AccountLogEntry::operator==(const AccountLogEntry &other) const {
    return serialNumber == other.getSerialNumber();
}
