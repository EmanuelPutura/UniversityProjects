#include <string.h>
#include <stdlib.h>
#include "validators.h"

#define MAX_VALID_YEAR 3000
#define MIN_VALID_YEAR 1900

bool validateMaterial(Material* material) {
    if (material == NULL) return false;
	return strcmp(getMaterialName(material), "") && strcmp(getMaterialSupplier(material), "")
		&& *(getMaterialQuantity(material)) > 0 && validateDate(getMaterialExpirationDate(material));
}

bool validateDate(Date* date) {
    if (date == NULL) return false;
    if (getDateYear(date) > MAX_VALID_YEAR || getDateYear(date) < MIN_VALID_YEAR) return false;
    if (getDateMonth(date) < 1 || getDateMonth(date) > 12) return false;
    if (getDateDay(date) < 1 || getDateDay(date) > 31) return false;

    if (getDateMonth(date) == 2) {
        if (leapDateYear(date)) return getDateDay(date) <= 29;
        else return getDateDay(date) <= 28;
    }

    if (getDateMonth(date) == 4 || getDateMonth(date) == 6 || getDateMonth(date) == 9 || getDateMonth(date) == 11)
        return (getDateDay(date) <= 30);
    return true;
}