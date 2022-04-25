#include "conversions.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef BUFSIZE
#define BUFSIZE 100
#endif


char* stringToLower(char* string) {
	char* converted_str = (char*)malloc(BUFSIZE * sizeof(char));
	if (converted_str == NULL) return NULL;

	for (int i = 0; string[i]; i++) {
		converted_str[i] = tolower(string[i]);
		converted_str[i + 1] = 0;
	}

	return converted_str;
}