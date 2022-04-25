#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include <domain/user.h>


class UserRepository
{
private:
    std::vector<User> elements;
    std::string file_name;
    char delimiter;
public:
    UserRepository(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const User& obj);
    void remove(const User& obj);

    inline const std::vector<User>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // USERREPOSITORY_H
