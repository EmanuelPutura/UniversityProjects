#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include <Domain/castle.h>


class Repository
{
private:
    std::vector<Castle> elements;
    std::string file_name;
    char delimiter;
public:
    Repository(const std::string& file_name, char delimiter = '|');

    void readFromFile();
    void writeToFile();

    void add(const Castle& castle);

    inline const std::vector<Castle>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // REPOSITORY_H
