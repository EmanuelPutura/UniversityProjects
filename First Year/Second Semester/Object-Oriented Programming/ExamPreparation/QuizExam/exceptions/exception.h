#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>



class Exception : public std::exception
{
private:
    std::string error;
public:
    Exception(const std::string& error);
    inline const std::string& getError() const { return error; }
};

#endif // EXCEPTION_H
