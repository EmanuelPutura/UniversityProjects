//
// Created by Emanuel on 20.06.2021.
//

#ifndef WRITTENEXAM_ITERATOR_H
#define WRITTENEXAM_ITERATOR_H

#include "Vector.h"

template <class T>
class Iterator {
private:
    T* elems;
    int current;
public:
    explicit Iterator(T* e);

    int getCurrent() const { return current; }
    void setCurrent(int c);

    T& operator* () const;
    bool operator!= (const Iterator<T>& other) const;
    void operator++ ();

};

template<class T>
Iterator<T>::Iterator(T* e) : elems(e), current(0) {
}

template<class T>
T &Iterator<T>::operator*() const {
    return elems[current];
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T> &other) const {
    return current != other.current;
}

template<class T>
void Iterator<T>::operator++() {
    current++;
}

template<class T>
void Iterator<T>::setCurrent(int c) {
    current = c;
}


#endif //WRITTENEXAM_ITERATOR_H
