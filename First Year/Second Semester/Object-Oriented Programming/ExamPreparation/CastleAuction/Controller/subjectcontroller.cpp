#include "subjectcontroller.h"

#include <QDebug>
#include <algorithm>

SubjectController::SubjectController() : repository {"../CastleAuction/files/castles.txt"}
{
    filtered_data = std::vector<Castle>();
//    auto data = repository.getData();
//    std::copy(data.begin(), data.end(), std::back_inserter(filtered_data));
}

SubjectController::~SubjectController()
{
    for (auto& observer : observers)
        delete observer;
}

void SubjectController::updateCurrentPrice(int index, int newPrice)
{
    repository.updateCurrentPrice(index, newPrice);
    auto element = repository.getData()[index];

    for (auto& elem : filtered_data) {
        if (elem.getName() == element.getName()) {
            elem.setCurrentPrice(newPrice);
            break;
        }
    }

    notify();
}

void SubjectController::addFilteredData(std::string name)
{
    for (const auto& el : filtered_data)
        if (el.getName() == name)
            return;

    for (const auto& elem : repository.getData()) {
        if (elem.getName() == name) {
            filtered_data.push_back(elem);
        }
    }
    notify();
}

void SubjectController::removeFilteredData(std::string name)
{
    auto it = std::find_if(filtered_data.begin(), filtered_data.end(), [&name](auto& el){
        return el.getName() == name;
    });
    if (it != filtered_data.end())
    {
        filtered_data.erase(it);
        notify();
    }
}
