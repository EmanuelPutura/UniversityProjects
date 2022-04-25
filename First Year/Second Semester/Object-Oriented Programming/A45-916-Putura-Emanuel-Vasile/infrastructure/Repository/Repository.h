//
// Created by Emanuel on 21.03.2021.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../AbstractRepository/AbstractRepository.h"

/**
 * Generic Repository Class
 */
template <class T>
class Repository : public AbstractRepository<T> {
public:
    /**
     * Adds an element to the repository
     * @param element: the element to be added
     */
    virtual void add(const T& element) override;

    /**
     * Removes an element from the repository
     * @param element: the element to be removed
     * @return: the index of the removed element or -1 if the element was not found
     */
    virtual void remove(const T& element) override;

    /**
     * Gets the index of an element of the repository
     * @param element: the element to be searched for
     * @return: the index of the element or -1 if the element was not found
     */
    virtual int getIndex(const T& element) override;

    /**
     * Updates an element of the repository
     * @param element: the element to be updated
     * @param new_element: the new value for the updated element
     * @return: the index of the element or -1 if the element was not found
     */
    virtual void update(const T& element, const T& new_element) override;

    /**
     * [] operator overloading
     */
    virtual const T& operator[](int index) override;

    /**
     * Getters
     */
    virtual inline int getLength() override { return this->data.size(); }
    virtual const std::vector<T>& getData() override { return this->data; }
};

#include "Repository.inl"
#endif
