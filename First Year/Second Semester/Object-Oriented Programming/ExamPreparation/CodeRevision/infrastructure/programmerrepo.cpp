#include "programmerrepo.h"

ProgrammerRepo::ProgrammerRepo(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void ProgrammerRepo::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);
            if (result.size() != 3)
                return;

            Programmer p {result[0], stoi(result[1]), stoi(result[2])};
            elements.push_back(p);
        }
        fin.close();
    }
}

void ProgrammerRepo::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getName() << ',' << el.getRevisedFiles() << ',' << el.getToRevise() << '\n';
        });
        fout.close();
    }
}

void ProgrammerRepo::add(const Programmer &obj)
{
//    readFromFile();
    elements.push_back(obj);
//    writeToFile();
}

void ProgrammerRepo::update(const Programmer &old, const Programmer &n)
{
    auto it = std::find_if(elements.begin(), elements.end(), [&old](const auto& e){
        return e.getName() == old.getName();
    });
    if (it == elements.end()) return;
    *it = n;
}

std::vector<std::string> ProgrammerRepo::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
