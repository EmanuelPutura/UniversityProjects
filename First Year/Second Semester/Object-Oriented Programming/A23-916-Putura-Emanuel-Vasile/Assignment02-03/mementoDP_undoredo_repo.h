/*
*  UndoRedo Repository implemented using the Memento Design Pattern
*/

#pragma once

#include "dynamic_array.h"
#include "materials_repository.h"

/*
*  MemUndoRedoRepo structure - memento design pattern undo/redo repository
*/
typedef struct {
	DynamicArray* array;
	int undo_index;
} MemUndoRedoRepo;

/*
*  Creates a new MemUndoRedoRepo object
*/
MemUndoRedoRepo* createMemUndoRedoRepo();

/*
*  Adds a new element to a MemUndoRedoRepo object
*/
void addMemUndoRedoRepo(MemUndoRedoRepo* repository, MaterialsRepository* repo_state);

/*
*  Gets the number of elements in a MemUndoRedoRepo repository
*/
int getLengthMemUndoRedoRepo(MemUndoRedoRepo* repository);

/*
*  Gets the undo index attribute of a MemUndoRedoRepo object
*/
int getUndoIndexMemUndoRedoRepo(MemUndoRedoRepo* repository);

/*
*  Gets the maximum index of an element in a MemUndoRedoRepo repository
*/
int getMaxIndexMemUndoRedoRepo(MemUndoRedoRepo* repository);

/*
*  Gets an element from an index in a MemUndoRedoRepo repository 
*/
MaterialsRepository* getFromIndexMemUndoRedoRepo(MemUndoRedoRepo* repository, int index);

/*
*  Sets the undo index attribute of a MemUndoRedoRepo object
*/
void setUndoIndexMemUndoRedoRepo(MemUndoRedoRepo* repository, int value);

/*
*  Sets an element from an index in a MemUndoRedoRepo repository
*/
void setIndexDataMemUndoRedoRepo(MemUndoRedoRepo* repository, MaterialsRepository* repo_state, int index);

/*
*  Removes an element from a MemUndoRedoRepo repository
*/
int removeMemUndoRedoRepo(MemUndoRedoRepo* repository, MaterialsRepository* repo_state);

/*
*  Destroys a MemUndoRedoRepo object
*/
void destroyMemUndoRedoRepo(MemUndoRedoRepo* repository);
