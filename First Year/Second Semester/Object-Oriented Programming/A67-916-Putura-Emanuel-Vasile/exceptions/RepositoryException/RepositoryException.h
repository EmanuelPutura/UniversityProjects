//
// Created by Emanuel on 10.04.2021.
//

#ifndef REPOSITORYEXCEPTION_H
#define REPOSITORYEXCEPTION_H

#include "../Exception/Exception.h"

class RepositoryException : public Exception {
public:
    explicit RepositoryException(const std::string& message = "") : Exception(message) {}
};

#endif
