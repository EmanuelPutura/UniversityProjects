#include "idearepo.h"

IdeaRepository::IdeaRepository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void IdeaRepository::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);

            if (result.size() != 4)
                return;

            Idea i {result[0], result[1], result[2], stoi(result[3])};
            elements.push_back(i);
        }
        fin.close();
    }
}

void IdeaRepository::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getDescription() << ',' << el.getStatus() <<  ',' << el.getCreator() << ',' << el.getAct() << '\n';
        });
        fout.close();
    }
}

void IdeaRepository::add(const Idea &obj)
{
//    readFromFile();
    elements.push_back(obj);
//    writeToFile();
}

void IdeaRepository::remove(const Idea &obj)
{
    auto it = std::find_if(elements.begin(), elements.end(), [&obj](const auto& el){
        return obj.getDescription() == el.getDescription();
    });

    if (it == elements.end())
        return;
    elements.erase(it);
}

void IdeaRepository::update(const Idea &id1, const Idea &id2)
{
    auto it = std::find_if(elements.begin(), elements.end(), [&id1](const auto& el){
        return id1.getDescription() == el.getDescription();
    });

    if (it == elements.end())
        return;
    *it = id2;
}

std::vector<std::string> IdeaRepository::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
