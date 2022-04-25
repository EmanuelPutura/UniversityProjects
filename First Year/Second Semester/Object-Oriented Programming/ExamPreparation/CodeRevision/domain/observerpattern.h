#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observer
{
public:
    virtual void update() = 0;
    virtual void buttonUpdate(bool flag) = 0;
};


class Subject
{
protected:
    std::vector<Observer*> observers;
public:
    Subject();

    void addObserver(Observer* obs);
    void notifyAll();
};


#endif // OBSERVER_H
