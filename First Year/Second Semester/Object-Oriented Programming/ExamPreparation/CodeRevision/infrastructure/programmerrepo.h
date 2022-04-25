#ifndef PROGRAMMERREPO_H
#define PROGRAMMERREPO_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include <domain/programmer.h>


class ProgrammerRepo
{
private:
    std::vector<Programmer> elements;
    std::string file_name;
    char delimiter;
public:
    ProgrammerRepo(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const Programmer& obj);
    void update(const Programmer& old, const Programmer& n);

    inline const std::vector<Programmer>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // PROGRAMMERREPO_H
