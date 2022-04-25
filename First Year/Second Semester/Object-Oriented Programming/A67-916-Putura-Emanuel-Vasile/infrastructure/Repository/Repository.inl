//
// Created by Emanuel on 21.03.2021.
//

#include "../../exceptions/RepositoryException/RepositoryException.h"

#include <algorithm>
#include <iostream>

template<class T>
void Repository<T>::add(const T& element) {
    if (find(this->data.begin(), this->data.end(), element) != this->data.end())
        throw RepositoryException("Attempted to add an existing element to the repository.\n");
    this->data.push_back(element);
}

template<class T>
void Repository<T>::remove(const T& element) {
    auto position = std::find(this->data.begin(), this->data.end(), element);
    if (position == this->data.end())
        throw RepositoryException("Attempted to remove a nonexistent element.\n");
    this->data.erase(position);
}

template<class T>
int Repository<T>::getIndex(const T& element) {
    auto position = std::find(this->data.begin(), this->data.end(), element);
    if (position == this->data.end())
        throw RepositoryException("The element was not found.\n");
    return position - this->data.begin();
}

template<class T>
void Repository<T>::update(const T &element, const T &new_element) {
    int index = getIndex(element);
    this->data[index] = new_element;
}

template<class T>
const T &Repository<T>::operator[](int index) {
    return this->data[index];
}
