//
// Created by Emanuel on 10.04.2021.
//

#ifndef ABSTRACTREPOSITORY_H
#define ABSTRACTREPOSITORY_H

#include <vector>

template <class T>
class AbstractRepository {
protected:
    std::vector<T> data;
public:
    virtual void add(const T& element) = 0;

    virtual void remove(const T& element) = 0;

    virtual int getIndex(const T& element) = 0;

    virtual void update(const T& element, const T& new_element) = 0;

    virtual const T& operator[](int index) = 0;

    virtual int getLength() = 0;
    virtual const std::vector<T>& getData() = 0;
};

#endif
