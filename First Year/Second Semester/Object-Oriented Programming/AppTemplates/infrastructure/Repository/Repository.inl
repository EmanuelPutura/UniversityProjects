//
// Created by Emanuel on 04.04.2021.
//

#include "Repository.h"

template<class T>
void Repository<T>::add(const T &element) {
    vector.push(element);
}

template<class T>
void Repository<T>::remove(const T &element) {
    vector.remove(element);
}

template<class T>
void Repository<T>::update(const T &element, const T &other) {
    auto index = vector.getIndex(element);
    if (index == -1)
        throw std::exception();
    vector[index] = other;
}

template<class T>
int Repository<T>::search(const T &element) const {
    return vector.getIndex(element);
}
