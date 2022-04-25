#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <exception>
#include <string>

class Exception : public std::exception
{
private:
    std::string message;
public:
    Exception(const std::string& message);

    inline const std::string& getMessage() const { return message; }
};

#endif // EXCEPTION_H
