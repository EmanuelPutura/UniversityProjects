//
// Created by Emanuel on 04.04.2021.
//

#include "DynamicVector.h"

#include <exception>

template<class T>
DynamicVector<T>::DynamicVector(size_t capacity) : capacity(capacity), length(0) {
    data = new T[capacity];
}

template<class T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &other) {
    length = other.length;
    capacity = other.capacity;
    delete[] data;
    data = new T[capacity];

    for (size_t i = 0; i < length; ++i)
        data[i] = other.data[i];
}

template<class T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector<T> &other) {
    length = other.length;
    capacity = other.capacity;
    delete[] data;
    data = new T[capacity];

    for (size_t i = 0; i < length; ++i)
        data[i] = other.data[i];
}

template<class T>
void DynamicVector<T>::resize() {
    capacity *= 2;
    T* new_data = new T[capacity];

    for (size_t i = 0; i < length; ++i)
        new_data[i] = data[i];

    delete[] data;
    data = new_data;
}

template <class T>
void DynamicVector<T>::push(const T& value) {
    if (length == capacity)
        resize();
    data[length++] = value;
}

template<class T>
int DynamicVector<T>::remove(const T& value) {
    int index = getIndex(value);
    if (index == -1) return -1;

    for (size_t i = index + 1; i < length; ++i)
        data[i - 1] = data[i];
    length--;
    return index;
}

template<class T>
int DynamicVector<T>::getIndex(const T& value) const{
    for (size_t i = 0; i < length; ++i)
        if (data[i] == value) return i;
    return -1;
}

template<class T>
T &DynamicVector<T>::operator[](int index) {
    if (index < 0 || index >= length)
        throw std::exception();
    return data[index];
}

template<class T>
DynamicVector<T>::~DynamicVector() {
    delete[] data;
}
