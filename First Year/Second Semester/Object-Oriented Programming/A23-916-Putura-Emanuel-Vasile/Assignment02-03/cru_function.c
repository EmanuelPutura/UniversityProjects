#pragma warning(disable:6386)

#include "cru_function.h"

#include <stdlib.h>

CRUFunction* createCRUFunction(int (*function)(), int param_count, ...) {
	va_list args;
	va_start(args, param_count);
	
	CRUFunction* cru_function = (CRUFunction*)malloc(sizeof(CRUFunction));
	if (cru_function == NULL) return NULL;

	cru_function->function = function;
	cru_function->param_count = param_count;
	cru_function->params = (void**)malloc(param_count * sizeof(void*));
	if (cru_function->params == NULL) return NULL;

	for (int i = 0; i < param_count; ++i) {
		cru_function->params[i] = (void*)va_arg(args, void*);
	}

	va_end(args);

	return cru_function;
}

void callCRUFunction(CRUFunction* cru_function) {
	if (cru_function->param_count == 6)
		cru_function->function(cru_function->params[0], cru_function->params[1], cru_function->params[2], cru_function->params[3], cru_function->params[4], cru_function->params[5]);
	else if (cru_function->param_count == 5)
		cru_function->function(cru_function->params[0], cru_function->params[1], cru_function->params[2], cru_function->params[3], cru_function->params[4]);
}

void destroyCRUFunction(CRUFunction* cru_function) {
	for (int i = 1; i < cru_function->param_count; ++i)
		free(cru_function->params[i]);
	free(cru_function->params);
	free(cru_function);
}
