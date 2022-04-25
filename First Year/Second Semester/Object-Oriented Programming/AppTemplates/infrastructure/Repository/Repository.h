//
// Created by Emanuel on 04.04.2021.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../DynamicVector/DynamicVector.h"

template <class T>
class Repository {
private:
    DynamicVector<T> vector;
public:
    void add(const T& element);

    void remove(const T& element);

    void update(const T& element, const T& other);

    int search(const T& element) const;

    inline T& operator[] (const int& index) { return vector[index]; }

    inline int getLength() const { return vector.getLength(); }
    inline T* getData() const { return vector.getData(); }
};

#include "Repository.inl"
#endif
