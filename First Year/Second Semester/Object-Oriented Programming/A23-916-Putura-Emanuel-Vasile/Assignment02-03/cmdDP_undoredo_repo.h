/*
*  UndoRedo Repository implementation using the Command Design Pattern
*/

#pragma once

#include "dynamic_array.h"
#include "undoredo_function.h"

/*
*  CmdUndoRedoRepo structure
*/
typedef struct {
	DynamicArray* array;
	int undo_index;
} CmdUndoRedoRepo;

/*
*  Creates a CmdUndoRedoRepo object
*/
CmdUndoRedoRepo* createCmdUndoRedoRepo();

/*
*  Adds an element to a CmdUndoRedoRepo repository
*/
void addCmdUndoRedoRepo(CmdUndoRedoRepo* repository, UndoRedoFunction* ur_function);

/*
*  Gets the length of a CmdUndoRedoRepo repository
*/
int getLengthCmdUndoRedoRepo(CmdUndoRedoRepo* repository);

/*
*  Gets the undo index of a CmdUndoRedoRepo repository
*/
int getUndoIndexCmdUndoRedoRepo(CmdUndoRedoRepo* repository);

/*
*  Gets an element from a CmdUndoRedoRepo repository
*/
UndoRedoFunction* getFromIndexCmdUndoRedoRepo(CmdUndoRedoRepo* repository, int index);

/*
*  Sets the undo index of a CmdUndoRedoRepo repository
*/
void setUndoIndexCmdUndoRedoRepo(CmdUndoRedoRepo* repository, int value);

/*
*  Updates an element from CmdUndoRedoRepo repository
*/
void setIndexDataCmdUndoRedoRepo(CmdUndoRedoRepo* repository, UndoRedoFunction* ur_function, int index);

/*
*  Destroys a CmdUndoRedoRepo object
*/
void destroyCmdUndoRedoRepo(CmdUndoRedoRepo* repository);
