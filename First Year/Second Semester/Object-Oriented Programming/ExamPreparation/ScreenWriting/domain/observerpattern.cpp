#include "observerpattern.h"


Subject::Subject()
{
}

void Subject::addObserver(Observer *obs)
{
    observers.push_back(obs);
}

void Subject::notifyAll()
{
    for (const auto& obs : observers)
        obs->update();
}
