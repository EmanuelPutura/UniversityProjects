//
// Created by Emanuel on 16.04.2021.
//

#ifndef ABSTRACTLAUNCHREPOSITORY_H
#define ABSTRACTLAUNCHREPOSITORY_H

#include "../Repository/Repository.h"

template <class T>
class AbstractLaunchRepository : public Repository<T> {
protected:
    std::string file_path;
public:
    explicit AbstractLaunchRepository(const std::string& file_path) : file_path(file_path) {}

    /**
     * Adds an element to the repository
     * @param element: the element to be added
     */
    virtual void add(const T& element) = 0;

    /**
     * Removes an element from the repository
     * @param element: the element to be removed
     * @return: the index of the removed element or -1 if the element was not found
     */
    virtual void remove(const T& element) = 0;

    /**
     * Updates an element of the repository
     * @param element: the element to be updated
     * @param new_element: the new value for the updated element
     * @return: the index of the element or -1 if the element was not found
     */
    virtual void update(const T& element, const T& new_element) = 0;

    virtual void writeToFile() const = 0;

    virtual std::string getPath() const = 0;
};

#endif
