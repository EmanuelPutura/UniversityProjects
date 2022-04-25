//
// Created by Emanuel on 16.04.2021.
//

#ifndef HTMLREPOSITORY_H
#define HTMLREPOSITORY_H

#include "../../domain/TrenchCoat/TrenchCoat.h"
#include "../AbstractLaunchRepository/AbstractLaunchRepository.h"

#include <fstream>
#include <sstream>

class HTMLCoatsRepository : public AbstractLaunchRepository<TrenchCoat> {
public:
    explicit HTMLCoatsRepository(const std::string& file_path = "") : AbstractLaunchRepository<TrenchCoat>(file_path) {
        writeToFile();
    }

    /**
     * Adds an element to the repository
     * @param element: the element to be added
     */
    void add(const TrenchCoat& element) override;

    /**
     * Removes an element from the repository
     * @param element: the element to be removed
     * @return: the index of the removed element or -1 if the element was not found
     */
    void remove(const TrenchCoat& element) override;

    /**
     * Updates an element of the repository
     * @param element: the element to be updated
     * @param new_element: the new value for the updated element
     * @return: the index of the element or -1 if the element was not found
     */
    void update(const TrenchCoat& element, const TrenchCoat& new_element) override;

    void writeToFile() const override;

    inline std::string getPath() const override { return this->file_path; }
};

#endif
