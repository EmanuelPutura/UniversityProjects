#ifndef ISSUEREPOSITORY_H
#define ISSUEREPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include <domain/writer.h>


class WriterRepository
{
private:
    std::vector<Writer> elements;
    std::string file_name;
    char delimiter;
public:
    WriterRepository(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const Writer& obj);
    void remove(const Writer& obj);
    void update(const Writer& old, const Writer& obj);

    inline const std::vector<Writer>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // ISSUEREPOSITORY_H
