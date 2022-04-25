#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include "domain/question.h"

class QuestionsRepository
{
private:
    std::vector<Question> elements;
    std::string file_name;
    char delimiter;
public:
    QuestionsRepository(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const Question& obj);
    void remove(const Question& obj);
    void update(const Question& id1, const Question& id2);

    void sort(bool id_sort = true);

    inline const std::vector<Question>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // USERREPOSITORY_H
