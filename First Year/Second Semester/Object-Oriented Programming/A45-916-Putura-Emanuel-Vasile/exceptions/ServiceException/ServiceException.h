//
// Created by Emanuel on 10.04.2021.
//

#ifndef SERVICEEXCEPTION_H
#define SERVICEEXCEPTION_H

#include "../Exception/Exception.h"

class ServiceException : public Exception {
public:
    explicit ServiceException(const std::string& message = "") : Exception(message) {}
};

#endif
