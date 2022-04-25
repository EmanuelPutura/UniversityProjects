#include "repository.h"

Repository::Repository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void Repository::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);
            if (result.size() != 4)
                return;

            Castle castle {result[0], result[1], stoi(result[2]), stoi(result[3])};
            elements.push_back(castle);
        }
        fin.close();
    }
}

void Repository::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getName() << delimiter << el.getLocation() << delimiter << el.getStartingPrice() << delimiter << el.getCurrentPrice() << '\n';
        });
        fout.close();
    }
}

void Repository::add(const Castle &obj)
{
    elements.push_back(obj);
}

std::vector<std::string> Repository::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
