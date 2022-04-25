#ifndef SOURCEFILEREPO_H
#define SOURCEFILEREPO_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <qDebug>

#include <domain/sourcefile.h>


class SourceFileRepo
{
private:
    std::vector<SourceFile> elements;
    std::string file_name;
    char delimiter;
public:
    SourceFileRepo(const std::string& file_name, char delimiter = ',');

    void readFromFile();
    void writeToFile();

    void add(const SourceFile& obj);
    void update(const SourceFile& old, const SourceFile& new_obj);

    inline const std::vector<SourceFile>& data() const { return elements; }
    inline int size() const { return elements.size(); }
private:
    std::vector<std::string> tokenize(const std::string& string, char delim);
};

#endif // SOURCEFILEREPO_H
