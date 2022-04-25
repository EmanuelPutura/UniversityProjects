#include "cmdDP_undoredo_repo.h"

#include <stdlib.h>

#define ARRAYCAPACITY 1000


CmdUndoRedoRepo* createCmdUndoRedoRepo() {
	CmdUndoRedoRepo* repository = (CmdUndoRedoRepo*)malloc(sizeof(CmdUndoRedoRepo));
	if (repository == NULL) return NULL;

	repository->array = createDynamicArray(ARRAYCAPACITY);
	if (repository->array == NULL) return NULL;

	repository->undo_index = -1;
	return repository;
}

void addCmdUndoRedoRepo(CmdUndoRedoRepo* repository, UndoRedoFunction* ur_function) {
	int count = 0;
	for (int i = repository->undo_index + 1; i < getSizeDA(repository->array); ++i) {
		destroyUndoRedoFunction(getElementDA(repository->array, i));
		count++;
	}
	setSizeDA(repository->array, getSizeDA(repository->array) - count);

	addDA(repository->array, ur_function);
	repository->undo_index += 1;
}

int getLengthCmdUndoRedoRepo(CmdUndoRedoRepo* repository) {
	return getSizeDA(repository->array);
}

int getUndoIndexCmdUndoRedoRepo(CmdUndoRedoRepo* repository) {
	return repository->undo_index;
}

UndoRedoFunction* getFromIndexCmdUndoRedoRepo(CmdUndoRedoRepo* repository, int index) {
	if (index < 0 || index >= getSizeDA(repository->array)) return NULL;
	return getDataDA(repository->array)[index];
}

void setUndoIndexCmdUndoRedoRepo(CmdUndoRedoRepo* repository, int value) {
	repository->undo_index = value;
}

void setIndexDataCmdUndoRedoRepo(CmdUndoRedoRepo* repository, UndoRedoFunction* ur_function, int index) {
	if (index < 0 || index >= getSizeDA(repository->array)) return;
	getDataDA(repository->array)[index] = ur_function;
}

void destroyCmdUndoRedoRepo(CmdUndoRedoRepo* repository) {
	destroyDynamicArray(repository->array, &destroyUndoRedoFunction);
	free(repository);
}
