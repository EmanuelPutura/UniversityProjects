#include "castlesrepository.h"

std::vector<std::string> CastlesRepository::tokenize(const std::string &str, char delimiter) const
{
    std::vector<std::string> result;
    std::stringstream stream(str);
    std::string token;

    while(getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

CastlesRepository::CastlesRepository(const std::string& fileName) : fileName(fileName)
{
    readFromFile();
}

void CastlesRepository::readFromFile()
{
    std::ifstream fin(fileName);
    std::string line;

    castles.clear();
    if (fin.is_open()) {
        while(getline(fin, line)) {
            auto tokens = tokenize(line, '|');
            if (tokens.size() != 4) return;

            Castle castle {tokens[0], tokens[1], stoi(tokens[2]), stoi(tokens[3])};
            castles.push_back(castle);
        }
        fin.close();
    }
}

void CastlesRepository::writeToFile()
{
    std::ofstream fout(fileName);

    if (fout.is_open()) {
        for (const auto& c : castles) {
            fout << c.getName() << '|' << c.getLocation() << '|' << c.getStartingPrice() << '|' << c.getCurrentPrice() << '\n';
        }
        fout.close();
    }
}

void CastlesRepository::add(const Castle &castle)
{
    readFromFile();
    castles.push_back(castle);
    writeToFile();
}

void CastlesRepository::updateCurrentPrice(int index, int newPrice)
{
    castles[index].setCurrentPrice(newPrice);
}
