/*
*  Comparison functions
*/

#pragma once

#include <stdbool.h>

/*
*  Comparison function between two strings (ASCII ascending order)
*/
bool asciiGreaterString(char* string1, char* string2);

/*
*  Comparison function between two strings (ASCII descending order)
*/
bool asciiLessString(char* string1, char* string2);

/*
*  Comparison function between two strings (alphabetical ascending order)
*/
bool alphaGreaterString(char* string1, char* string2);

/*
*  Comparison function between two strings (alphabetical descending order)
*/
bool alphaLessString(char* string1, char* string2);

/*
*  Comparison function between two integers (ascending order)
*/
bool greaterInteger(int* a, int* b);

/*
*  Comparison function between two integers (descending order)
*/
bool lessInteger(int* a, int* b);
