#include "observerpattern.h"

#include <ObserverWindow.h>
#include <algorithm>
#include <QDebug>

void Subject::addObserver(Observer *observer)
{
    observers.push_back(observer);
}

void Subject::removeObserver(Observer *observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Subject::notify()
{
    for (const auto& obs : observers)
        obs->update();
}

void Subject::notifyCheckBox(std::string castle, bool value)
{
    for (const auto& obs : observers)
        obs->updateCheckBox(castle, value);
}
