#include "issuerepository.h"

IssueRepository::IssueRepository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void IssueRepository::readFromFile()
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

            Issue i {result[0], result[1], result[2], result[3]};
            elements.push_back(i);
        }
        fin.close();
    }
}

void IssueRepository::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getDescription() << ',' << el.getStatus() << ',' << el.getReporter();
            if (el.getSolver() == "") fout << '\n';
            else fout << ',' << el.getSolver() << '\n';
        });
        fout.close();
    }
}

void IssueRepository::add(const Issue &obj)
{
//    readFromFile();
    elements.push_back(obj);
//    writeToFile();
}

void IssueRepository::remove(const Issue &obj)
{
//    readFromFile();
    auto it = std::find_if(elements.begin(), elements.end(), [&obj](const auto& el){
        return obj.getDescription() == el.getDescription();
    });

    if (it == elements.end())
        return;
    elements.erase(it);
    //    writeToFile();
}

void IssueRepository::update(const Issue &old, const Issue &obj)
{
//    readFromFile();
    auto it = std::find_if(elements.begin(), elements.end(), [&old](const auto& el){
        return old.getDescription() == el.getDescription();
    });

    if (it == elements.end())
        return;
    *it = obj;
//    writeToFile();
}

std::vector<std::string> IssueRepository::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
