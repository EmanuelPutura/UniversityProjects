//
// Created by Emanuel on 22.10.2022.
//

#include <ctime>
#include <cstdlib>
#include "RandomGenerator.h"

int RandomGenerator::generateRandomIntBetween(int min, int max) {
    return rand() % (max - min + 1) + min;
}
