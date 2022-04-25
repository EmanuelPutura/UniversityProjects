/*
*  Validators Module. Contains validation functions for Material and Date objects
*/

#pragma once
#include <stdbool.h>
#include "material.h"
#include "date.h"

/*
*  Validates a Material object
*  <param material> - pointer to a Material object
*/
bool validateMaterial(Material* material);

/*
*  Validates a Date object
*  <param date> - pointer to a Date object
*/
bool validateDate(Date* date);