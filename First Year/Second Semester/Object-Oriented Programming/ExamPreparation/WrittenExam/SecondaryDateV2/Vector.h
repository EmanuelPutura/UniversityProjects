//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAM_VECTOR_H
#define WRITTENEXAM_VECTOR_H

#define CAP 10

#include <iostream>
#include <algorithm>

template <class T>
class Iterator;

class excep : public std::exception {
    const char* what() const noexcept {
        return "Element does not exist";
    }
};

template<class T>
class Vector {
private:
    T* elems;
    int len, cap;
public:
    Vector();
    ~Vector();

    Vector<T>& add(const T& e);

    auto begin() const;
    auto end() const;

    inline T* getElems() const { return elems; }

    Vector<T>& operator- (const T& el);
private:
    void resize();
};

template <class T>
Vector<T>::Vector() : elems(new T[CAP]), cap(CAP), len(0) {
}

template<class T>
Vector<T> &Vector<T>::add(const T &e) {
    if (len == cap)
        resize();

    elems[len] = e;
    len++;
    return *this;
}

template<class T>
void Vector<T>::resize() {
    auto nelems = new T[cap * 2];

    for (int i = 0; i < cap; ++i)
        nelems[i] = elems[i];
    delete elems;

    elems = nelems;
    cap *= 2;
}

template<class T>
Vector<T>::~Vector() {
    delete elems;
}

template<class T>
auto Vector<T>::begin() const {
    return Iterator<T>(elems);
}

template<class T>
auto Vector<T>::end() const {
    auto it = Iterator<T>(elems);
    it.setCurrent(len);
    return it;
}

template<class T>
Vector<T> &Vector<T>::operator- (const T& el) {
    for (int i = 0; i < len; ++i) {
        if (elems[i] == el) {
            for (int j = i; j < len - 1; ++j)
                elems[j] = elems[j + 1];
            len--;
            return *this;
        }
    }
    throw excep();
}

#include "Iterator.h"

#endif //WRITTENEXAM_VECTOR_H
