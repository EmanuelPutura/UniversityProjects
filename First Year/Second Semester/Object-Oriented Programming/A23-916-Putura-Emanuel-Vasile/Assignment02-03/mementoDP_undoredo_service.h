/*
*  MemUndoRedoService Module - UndoRedo Service for the Memento Design Pattern undo/redo implementation
*/

#pragma once

#include "mementoDP_undoredo_repo.h"
#include "materials_repository.h"

/*
*  MemUndoRedoService structure
*/
typedef struct {
	MemUndoRedoRepo* repository;
} MemUndoRedoService;

/*
*  Creates a MemUndoRedoService object
*/
MemUndoRedoService* createMemUndoRedoService(MemUndoRedoRepo* repository);

/*
*  Adds a MemUndoRedoService object to the repository
*/
void addMemUndoRedoService(MemUndoRedoService* service, MaterialsRepository* repository);

/*
*  Gets a MemUndoRedoService object from an index from the repository
*/
MaterialsRepository* getFromIndexMemUndoRedoService(MemUndoRedoService* service, int index);

/*
*  Sets/updates a MemUndoRedoService object from an index from the repository
*/
void setIndexDataMemUndoRedoService(MemUndoRedoService* service, MaterialsRepository* repository, int index);

/*
*  Unodes an operation
*/
MaterialsRepository* undoMemUndoRedoService(MemUndoRedoService* service);

/*
*  Redoes an operation
*/
MaterialsRepository* redoMemUndoRedoService(MemUndoRedoService* service);

/*
*  Destroys an MemUndoRedoService object
*/
void destroyMemUndoRedoService(MemUndoRedoService* service);
