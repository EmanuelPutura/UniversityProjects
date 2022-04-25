//
// Created by Emanuel on 10.04.2021.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception {
protected:
    std::string message;
public:
    explicit Exception(const std::string& message="") : std::exception(), message(message) {}

    inline const std::string& getMessage() const { return message; }
};

#endif
