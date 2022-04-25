//
// Created by Emanuel on 11.04.2021.
//

#ifndef FILEREPOSITORY_H
#define FILEREPOSITORY_H

#include "../Repository/Repository.h"

#include <iostream>
#include <fstream>

#include <domain/TrenchCoat/TrenchCoat.h>

template <class T>
class FileRepository : public Repository<T> {
private:
    std::string file_path;

    void readDataFromFile();
    void writeDataToFile() const;
public:
    FileRepository(const std::string& file_path) : Repository<T>(), file_path(file_path) {}

    /**
     * Adds an element to the repository
     * @param element: the element to be added
     */
    void add(const T& element) override;

    /**
     * Removes an element from the repository
     * @param element: the element to be removed
     * @return: the index of the removed element or -1 if the element was not found
     */
     void remove(const T& element) override;

    /**
     * Gets the index of an element of the repository
     * @param element: the element to be searched for
     * @return: the index of the element or -1 if the element was not found
     */
    int getIndex(const T& element) override;

    /**
     * Updates an element of the repository
     * @param element: the element to be updated
     * @param new_element: the new value for the updated element
     * @return: the index of the element or -1 if the element was not found
     */
    void update(const T& element, const T& new_element) override;

    /**
     * [] operator overloading
     */
    const T& operator[](int index) override;

    /**
     * Getters
     */
    int getLength() override;
    const std::vector<T>& getData() override;
};

template<class T>
void FileRepository<T>::readDataFromFile() {
    std::ifstream fin(file_path);

    if (fin.is_open()) {
        this->data.clear();
        T element;
        while (fin >> element)
            this->data.push_back(element);
        fin.close();
    }
    else {
        std::ofstream fout(file_path);
        fout.close();
    }
}

template<class T>
void FileRepository<T>::writeDataToFile() const {
    std::ofstream fout(file_path);
    if (fout.is_open()) {
        std::for_each(this->data.begin(), this->data.end(), [&fout](const TrenchCoat& el){ fout << el << '\n'; });
        fout.close();
    }
    else throw RepositoryException("The file cannot be opened.\n");
}

template<class T>
void FileRepository<T>::add(const T &element) {
    readDataFromFile();
    Repository<T>::add(element);
    writeDataToFile();
}

template<class T>
void FileRepository<T>::remove(const T &element) {
    readDataFromFile();
    Repository<T>::remove(element);
    writeDataToFile();
}

template<class T>
int FileRepository<T>::getIndex(const T &element) {
    readDataFromFile();
    return Repository<T>::getIndex(element);
}

template<class T>
void FileRepository<T>::update(const T &element, const T &new_element) {
    readDataFromFile();
    Repository<T>::update(element, new_element);
    writeDataToFile();
}

template<class T>
const T &FileRepository<T>::operator[](int index) {
    readDataFromFile();
    return Repository<T>::operator[](index);
}

template<class T>
int FileRepository<T>::getLength() {
    readDataFromFile();
    return Repository<T>::getLength();
}

template<class T>
const std::vector<T> &FileRepository<T>::getData() {
    readDataFromFile();
    return Repository<T>::getData();
}

#endif
