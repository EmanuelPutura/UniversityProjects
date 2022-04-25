/*
*  UndoRedoFunction module
*/

#pragma once

#include "cru_function.h"

/*
*  UndoRedoFunction structure - its attributes are two CRUFunction objects representing an undo and a redo function
*/
typedef struct {
	CRUFunction *undo_function, *redo_function;
} UndoRedoFunction;

/*
*  Creates an UndoRedoFunction object
*/
UndoRedoFunction* createUndoRedoFunction(CRUFunction* undo_func, CRUFunction* redo_func);

/*
*  Undoes an operation
*/
void undoFunction(UndoRedoFunction* ur_function);

/*
*  Redoes an operation
*/
void redoFunction(UndoRedoFunction* ur_function);

/*
*  Destroys an UndoRedoFunction object
*/
void destroyUndoRedoFunction(UndoRedoFunction* ur_function);
