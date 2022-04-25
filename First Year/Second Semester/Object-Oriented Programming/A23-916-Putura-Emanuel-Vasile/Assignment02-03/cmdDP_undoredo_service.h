/*
*  CmdUndoRedoService Module - UndoRedo Service for the Command Design Pattern undo/redo implementation
*/

#pragma once

#include "cmdDP_undoredo_repo.h"
#include "undoredo_function.h"

/*
*  CmdUndoRedoService structure
*/
typedef struct {
	CmdUndoRedoRepo* repository;
} CmdUndoRedoService;

/*
*  Creates a CmdUndoRedoService object
*/
CmdUndoRedoService* createCmdUndoRedoService(CmdUndoRedoRepo* repository);

/*
*  Adds a CmdUndoRedoService object to the repository
*/
void addCmdUndoRedoService(CmdUndoRedoService* service, UndoRedoFunction* function);

/*
*  Gets a CmdUndoRedoService object from an index from the repository
*/
UndoRedoFunction* getFromIndexCmdUndoRedoService(CmdUndoRedoService* service, int index);

/*
*  Sets/updates a CmdUndoRedoService object from an index from the repository
*/
void setIndexDataCmdUndoRedoService(CmdUndoRedoService* service, UndoRedoFunction* function, int index);

/*
*  Undoes an operation
*/
int undoCmdUndoRedoService(CmdUndoRedoService* service);

/*
*  Redoes an operation
*/
int redoCmdUndoRedoService(CmdUndoRedoService* service);

/*
*  Destroys a CmdUndoRedoService object
*/
void destroyCmdUndoRedoService(CmdUndoRedoService* service);
