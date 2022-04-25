#include "mementoDP_undoredo_repo.h"

#include <stdlib.h>

#define ARRAYCAPACITY 1000

MemUndoRedoRepo* createMemUndoRedoRepo() {
	MemUndoRedoRepo* repository = (MemUndoRedoRepo*)malloc(sizeof(MemUndoRedoRepo));
	if (repository == NULL) return NULL;

	repository->array = createDynamicArray(ARRAYCAPACITY);
	if (repository->array == NULL) return NULL;

	addDA(repository->array, createMaterialsRepository());

	repository->undo_index = 0;
	return repository;
}

void addMemUndoRedoRepo(MemUndoRedoRepo* repository, MaterialsRepository* repo_state) {
	int max_index = getSizeDA(repository->array) - 1;
	if (repository->undo_index != max_index) {
		for (int i = repository->undo_index + 1; i <= max_index; ++i)
			removeMemUndoRedoRepo(repository, getDataDA(repository->array)[i]);
	}

	addDA(repository->array, repo_state);
	repository->undo_index += 1;
}

int getLengthMemUndoRedoRepo(MemUndoRedoRepo* repository) {
	return getSizeDA(repository->array);
}

int getUndoIndexMemUndoRedoRepo(MemUndoRedoRepo* repository) {
	return repository->undo_index;
}

int getMaxIndexMemUndoRedoRepo(MemUndoRedoRepo* repository) {
	return getSizeDA(repository->array) - 1;
}

MaterialsRepository* getFromIndexMemUndoRedoRepo(MemUndoRedoRepo* repository, int index) {
	if (index < 0 || index >= getSizeDA(repository->array)) return NULL;
	return getDataDA(repository->array)[index];
}

void setUndoIndexMemUndoRedoRepo(MemUndoRedoRepo* repository, int value) {
	repository->undo_index = value;
}

void setIndexDataMemUndoRedoRepo(MemUndoRedoRepo* repository, MaterialsRepository* repo_state, int index) {
	if (index < 0 || index >= getSizeDA(repository->array)) return;
	getDataDA(repository->array)[index] = repo_state;
}

int removeMemUndoRedoRepo(MemUndoRedoRepo* repository, MaterialsRepository* repo_state) {
	return removeDA(repository->array, repo_state, &destroyMaterialsRepository, &equalMaterialsRepository);
}

void destroyMemUndoRedoRepo(MemUndoRedoRepo* repository) {
	destroyDynamicArray(repository->array, &destroyMaterialsRepository);
	free(repository);
}
