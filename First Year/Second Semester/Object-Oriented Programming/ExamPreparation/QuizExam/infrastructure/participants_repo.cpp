//#include "participants_repo.h"

//ParticipantsRepository::ParticipantsRepository(const std::string &file_name, char delimiter) : file_name(file_name), delimiter(delimiter)
//{
//    readFromFile();
//}

//void ParticipantsRepository::readFromFile()
//{
//    std::ifstream fin(file_name);
//    std::string line;

//    elements.clear();
//    if (fin.is_open()) {
//        while (getline(fin, line)) {
//            auto result = tokenize(line, delimiter);

//            if (result.size() != 2)
//                return;

//            Participant p {result[0], stoi(result[1])};
//            elements.push_back(p);
//        }
//        fin.close();
//    }
//}

//void ParticipantsRepository::writeToFile()
//{
//    std::ofstream fout(file_name);
//    if (fout.is_open()) {
//        std::for_each(elements.begin(), elements.end(), [&fout, this](const auto& el){
//            fout << el.getName() << ',' << el.getScore() << '\n';
//        });
//        fout.close();
//    }
//}

//void ParticipantsRepository::add(const Participant &obj)
//{
////    readFromFile();
//    elements.push_back(obj);
////    writeToFile();
//}

//void ParticipantsRepository::remove(const Participant &obj)
//{
//    /*
//    auto it = std::find_if(elements.begin(), elements.end(), [&obj](const auto& el){
//        return obj.getName() == el.getName();
//    });

//    if (it == elements.end())
//        return;
//    elements.erase(it);*/
//}

//void ParticipantsRepository::update(const Participant &id1, const Participant &id2)
//{
////    auto it = std::find_if(elements.begin(), elements.end(), [&id1](const auto& el){
////        return id1.getDescription() == el.getDescription();
////    });

////    if (it == elements.end())
////        return;
////    *it = id2;
//}

//std::vector<std::string> ParticipantsRepository::tokenize(const std::string &string, char delim)
//{
//    std::vector<std::string> result;
//    std::stringstream stream {string};
//    std::string token;

//    while (getline(stream, token, delim))
//        result.push_back(token);
//    return result;
//}
