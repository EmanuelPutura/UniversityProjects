//
// Created by Emanuel on 10.04.2021.
//

#ifndef CONSOLEUIEXCEPTION_H
#define CONSOLEUIEXCEPTION_H

#include "../Exception/Exception.h"

class ConsoleUIException : public Exception {
public:
    explicit ConsoleUIException(const std::string& message = "") : Exception(message) {}
};

#endif
