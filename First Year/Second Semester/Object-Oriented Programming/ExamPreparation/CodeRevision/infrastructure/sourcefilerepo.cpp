#include "sourcefilerepo.h"

SourceFileRepo::SourceFileRepo(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void SourceFileRepo::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);

            if (result.size() == 3)
                result.push_back("");
            if (result.size() != 4)
                return;

            SourceFile s {result[0], result[1], result[2], result[3]};
            elements.push_back(s);
        }
        fin.close();
    }
}

void SourceFileRepo::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getName() << ',' << el.getStatus() << ',' << el.getCreator() << ',' << el.getReviewer() << '\n';
        });
        fout.close();
    }
}

void SourceFileRepo::add(const SourceFile &obj)
{
//    readFromFile();
    elements.push_back(obj);
//    writeToFile();
}

void SourceFileRepo::update(const SourceFile &old, const SourceFile &new_obj)
{
    auto it = std::find_if(elements.begin(), elements.end(), [&old](const auto& e){
        return e.getName() == old.getName();
    });
    if (it == elements.end()) return;
    *it = new_obj;
}

std::vector<std::string> SourceFileRepo::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
