#ifndef ISSUEREPOSITORY_H
#define ISSUEREPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>
#include <domain/issue.h>


class IssueRepository
{
private:
    std::vector<Issue> elements;
    std::string file_name;
    char delimiter;
public:
    IssueRepository(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const Issue& obj);
    void remove(const Issue& obj);
    void update(const Issue& old, const Issue& obj);

    inline const std::vector<Issue>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // ISSUEREPOSITORY_H
