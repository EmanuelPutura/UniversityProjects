#ifndef CASTLESREPOSITORY_H
#define CASTLESREPOSITORY_H

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

#include <Domain/castle.h>

class CastlesRepository
{
private:
    std::vector<Castle> castles;
    std::string fileName;

    std::vector<std::string> tokenize(const std::string& str, char delimiter) const;
public:
    CastlesRepository(const std::string& fileName);

    void readFromFile();
    void writeToFile();

    void add(const Castle& castle);
    void updateCurrentPrice(int index, int newPrice);

    inline const std::vector<Castle>& getData() { return castles; }
    inline int getLength() const { return castles.size(); }
};

#endif // CASTLESREPOSITORY_H
