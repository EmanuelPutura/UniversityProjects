/*
*  CRUFunction Module
*/

#pragma once

#include <stdarg.h> 
#include <stdbool.h>

/*
*  CRUFunction structure - used to store data about a function (pointer to that function, parameters of a function etc.)
*/
typedef struct {
	int (*function)();
	int param_count;
	void **params;
} CRUFunction;

/*
*  Creates a CRUFunction object
*/
CRUFunction* createCRUFunction(int (*function)(), int param_count, ...);

/*
*  Calls a function stored in a CRUFunction object
*/
void callCRUFunction(CRUFunction* cru_function);

/*
*  Destroys a CRUFunction object
*/
void destroyCRUFunction(CRUFunction* cru_function);
