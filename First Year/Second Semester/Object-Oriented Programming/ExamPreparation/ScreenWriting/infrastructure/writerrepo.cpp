#include "writerrepo.h"

WriterRepository::WriterRepository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void WriterRepository::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);

            if (result.size() != 2)
                return;

            Writer w {result[0], result[1]};
            elements.push_back(w);
        }
        fin.close();
    }
}

void WriterRepository::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getName() << ',' << el.getExpertise() << '\n';
        });
        fout.close();
    }
}

void WriterRepository::add(const Writer &obj)
{
//    readFromFile();
    elements.push_back(obj);
//    writeToFile();
}

void WriterRepository::remove(const Writer &obj)
{
////    readFromFile();
//    auto it = std::find_if(elements.begin(), elements.end(), [&obj](const auto& el){
//        return obj.getDescription() == el.getDescription();
//    });

//    if (it == elements.end())
//        return;
//    elements.erase(it);
//    //    writeToFile();
}

void WriterRepository::update(const Writer &old, const Writer &obj)
{
////    readFromFile();
//    auto it = std::find_if(elements.begin(), elements.end(), [&old](const auto& el){
//        return old.getDescription() == el.getDescription();
//    });

//    if (it == elements.end())
//        return;
//    *it = obj;
////    writeToFile();
}

std::vector<std::string> WriterRepository::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
