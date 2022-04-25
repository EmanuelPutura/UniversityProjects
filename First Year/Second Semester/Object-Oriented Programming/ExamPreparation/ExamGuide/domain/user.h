#ifndef USER_H
#define USER_H

#include <string>



class User
{
private:
    std::string name, type;
public:
    User();
    User(const std::string& n, const std::string& t);

    inline const std::string& getName() const { return name; }
    inline const std::string& getType() const { return type; }
};

#endif // USER_H
