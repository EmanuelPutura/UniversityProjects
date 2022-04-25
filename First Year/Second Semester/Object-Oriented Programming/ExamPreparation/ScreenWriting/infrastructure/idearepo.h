#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include <domain/idea.h>


class IdeaRepository
{
private:
    std::vector<Idea> elements;
    std::string file_name;
    char delimiter;
public:
    IdeaRepository(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const Idea& obj);
    void remove(const Idea& obj);
    void update(const Idea& id1, const Idea& id2);

    inline const std::vector<Idea>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // USERREPOSITORY_H
