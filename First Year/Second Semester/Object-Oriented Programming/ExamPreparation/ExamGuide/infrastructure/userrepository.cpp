#include "userrepository.h"

UserRepository::UserRepository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void UserRepository::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);

            if (result.size() != 2)
                return;

            User u {result[0], result[1]};
            elements.push_back(u);
        }
        fin.close();
    }
}

void UserRepository::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getName() << ',' << el.getType() << '\n';
        });
        fout.close();
    }
}

void UserRepository::add(const User &obj)
{
    readFromFile();
    elements.push_back(obj);
    writeToFile();
}

void UserRepository::remove(const User &obj)
{
    auto it = std::find_if(elements.begin(), elements.end(), [&obj](const auto& el){
        return obj.getName() == el.getName();
    });

    if (it == elements.end())
        return;
    elements.erase(it);
}

std::vector<std::string> UserRepository::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
