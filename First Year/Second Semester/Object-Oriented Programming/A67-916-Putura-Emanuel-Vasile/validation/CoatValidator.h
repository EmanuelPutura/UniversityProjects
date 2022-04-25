//
// Created by Emanuel on 21.03.2021.
//

#ifndef COATVALIDATOR_H
#define COATVALIDATOR_H

#include <string>
#include "../domain/TrenchCoat/TrenchCoat.h"

/**
 * CoatValidator Class
 * Validates a TrenchCoat object
 */
class CoatValidator {
private:
    std::string errors = "";
public:
    /**
     * Validates a TrenchCoat object
     * @param coat: the TrenchCoat object to be validated
     * @return: true if the TrenchCoat object is valid, false else
     */
    bool validate(const TrenchCoat& coat);

    /**
     * Errors Getter
     */
    inline std::string getErrors() const { return errors; }
};

#endif
