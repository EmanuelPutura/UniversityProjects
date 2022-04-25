#include "questions_repo.h"

QuestionsRepository::QuestionsRepository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
{
    readFromFile();
}

void QuestionsRepository::readFromFile()
{
    std::ifstream fin(file_name);
    std::string line;

    elements.clear();
    if (fin.is_open()) {
        while (getline(fin, line)) {
            auto result = tokenize(line, delimiter);

            if (result.size() != 4)
                return;

            Question q {stoi(result[0]), result[1], result[2], stoi(result[3])};
            elements.push_back(q);
        }
        fin.close();
    }
}

void QuestionsRepository::writeToFile()
{
    std::ofstream fout(file_name);
    if (fout.is_open()) {
        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
            fout << el.getID() << ',' << el.getText() <<  ',' << el.getCorrect() << ',' << el.getScore() << '\n';
        });
        fout.close();
    }
}

void QuestionsRepository::add(const Question &obj)
{
//    readFromFile();
    elements.push_back(obj);
//    writeToFile();
}

void QuestionsRepository::remove(const Question &obj)
{
    /*
    auto it = std::find_if(elements.begin(), elements.end(), [&obj](const auto& el){
        return obj.getName() == el.getName();
    });

    if (it == elements.end())
        return;
    elements.erase(it);*/
}

void QuestionsRepository::update(const Question &id1, const Question &id2)
{
//    auto it = std::find_if(elements.begin(), elements.end(), [&id1](const auto& el){
//        return id1.getDescription() == el.getDescription();
//    });

//    if (it == elements.end())
//        return;
    //    *it = id2;
}

void QuestionsRepository::sort(bool id_sort)
{
    std::sort(elements.begin(), elements.end(), [id_sort](const auto& el1, const auto& el2){
        if (id_sort)
            return el1.getID() < el2.getID();
        else return el1.getScore() > el2.getScore();
    });
}

std::vector<std::string> QuestionsRepository::tokenize(const std::string &string, char delim)
{
    std::vector<std::string> result;
    std::stringstream stream {string};
    std::string token;

    while (getline(stream, token, delim))
        result.push_back(token);
    return result;
}
