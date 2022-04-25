#include "comparison_functionc.h"
#include "conversions.h"

#include <string.h>
#include <stdlib.h>


bool asciiGreaterString(char* string1, char* string2) {
	return strcmp(string1, string2) > 0;
}

bool asciiLessString(char* string1, char* string2) {
	return strcmp(string1, string2) < 0;
}

bool alphaGreaterString(char* string1, char* string2) {
	char* converted_string1 = stringToLower(string1);
	char* converted_string2 = stringToLower(string2);

	int return_value = strcmp(converted_string1, converted_string2) > 0;
	free(converted_string1);
	free(converted_string2);

	return return_value;
}

bool alphaLessString(char* string1, char* string2) {
	char* converted_string1 = stringToLower(string1);
	char* converted_string2 = stringToLower(string2);

	int return_value = strcmp(converted_string1, converted_string2) < 0;
	free(converted_string1);
	free(converted_string2);

	return return_value;
}

bool greaterInteger(int* a, int* b) {
	return *a > *b;
}

bool lessInteger(int* a, int* b) {
	return *a < *b;
}
