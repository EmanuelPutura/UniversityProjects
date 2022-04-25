#include "undoredo_function.h"

#include <stdlib.h>

UndoRedoFunction* createUndoRedoFunction(CRUFunction* undo_func, CRUFunction* redo_func) {
	UndoRedoFunction* ur_function = (UndoRedoFunction*)malloc(sizeof(UndoRedoFunction));
	if (ur_function == NULL) return NULL;

	ur_function->undo_function = undo_func;
	ur_function->redo_function = redo_func;

	return ur_function;
}

void undoFunction(UndoRedoFunction* ur_function) {
	callCRUFunction(ur_function->undo_function);
}

void redoFunction(UndoRedoFunction* ur_function) {
	callCRUFunction(ur_function->redo_function);
}

void destroyUndoRedoFunction(UndoRedoFunction* ur_function) {
	destroyCRUFunction(ur_function->undo_function);
	destroyCRUFunction(ur_function->redo_function);
	free(ur_function);
}
