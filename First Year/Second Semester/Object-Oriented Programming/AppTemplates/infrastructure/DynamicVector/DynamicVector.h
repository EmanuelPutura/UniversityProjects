//
// Created by Emanuel on 04.04.2021.
//

#ifndef DYNAMICVECTOR_H
#define DYNAMICVECTOR_H
#ifndef CAPACITY
#define CAPACITY 100
#endif

#include <cstddef>

/**
 * Generic DynamicVector Class
 */
template <class T>
class DynamicVector {
private:
    T* data {nullptr};
    size_t length {0}, capacity;
public:
    explicit DynamicVector(size_t capacity = CAPACITY);
    DynamicVector(const DynamicVector<T>& other);

    DynamicVector<T>& operator= (const DynamicVector<T>& other);

    /**
     * Resizes the vector. The capacity is doubled
     */
    void resize();

    /**
     * Adds a new element to the end of the vector
     * @param value: the value to be added to the vector
     */
    void push(const T& value);

    /**
     * Removes an element from the vector
     * @param value: the value to be removed from the vector
     * @return: the index of the removed value or -1 if the value is not an element of the vector
     */
    int remove(const T& value);

    /**
     * Gets the index of an element of the vector
     * @param value: an element of the vector
     * @return: the index of the searched element or -1 if the element is not found
     */
    int getIndex(const T& value) const;

    /**
     * [] operator overloading
     */
    T& operator[](int index);

    /**
     * Getters
     */
    inline size_t getLength() const { return this->length; }
    inline size_t getCapacity() const { return this->capacity; }
    inline T* getData() const { return data; }

    ~DynamicVector();
};

#include "DynamicVector.inl"
#endif
