//
// Created by Emanuel on 16.04.2021.
//

#ifndef CSVREPOSITORY_H
#define CSVREPOSITORY_H

#include <infrastructure/AbstractLaunchRepository/AbstractLaunchRepository.h>
#include "../Repository/Repository.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <domain/TrenchCoat/TrenchCoat.h>

template <class T>
class CSVRepository : public AbstractLaunchRepository<T> {
public:
    explicit CSVRepository(const std::string& file_path = "") : AbstractLaunchRepository<T>(file_path) {
        writeToFile();
    }

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
     * Updates an element of the repository
     * @param element: the element to be updated
     * @param new_element: the new value for the updated element
     * @return: the index of the element or -1 if the element was not found
     */
    void update(const T& element, const T& new_element) override;

    void writeToFile() const override;

    inline std::string getPath() const override { return this->file_path; }
};

template<class T>
void CSVRepository<T>::add(const T &element) {
    Repository<T>::add(element);
    writeToFile();
}

template<class T>
void CSVRepository<T>::remove(const T &element) {
    Repository<T>::remove(element);
    writeToFile();
}

template<class T>
void CSVRepository<T>::update(const T &element, const T &new_element) {
    Repository<T>::update(element, new_element);
    writeToFile();
}

template<class T>
void CSVRepository<T>::writeToFile() const {
    if (this->file_path == "") return;
    std::ofstream fout(this->file_path);
    if (fout.is_open()) {
        std::stringbuf buffer;
        std::ostream out(&buffer);

        std::for_each(this->data.begin(), this->data.end(), [&out](const TrenchCoat& el){ out << el << '\n'; });

        std::string csv_format = buffer.str();
        std::replace(csv_format.begin(), csv_format.end(), ' ', ',');

        fout << csv_format;
        fout.close();
    }
    else throw RepositoryException("The file cannot be opened.\n");
}

#endif
