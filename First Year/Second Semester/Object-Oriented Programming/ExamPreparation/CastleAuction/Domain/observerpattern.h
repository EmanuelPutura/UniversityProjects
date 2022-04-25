#ifndef OBSERVERPATTERN_H
#define OBSERVERPATTERN_H

#include <string>
#include <vector>


class Observer
{
public:
    virtual void update() = 0;
    virtual void updateCheckBox(std::string castle, bool value) = 0;
};


class Subject
{
protected:
    std::vector<Observer*> observers;
public:
    Subject();

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notify();
    void notifyCheckBox(std::string castle, bool value);
};


#endif // OBSERVERPATTERN_H
