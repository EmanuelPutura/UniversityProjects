#include "mementoDP_undoredo_service.h"

#include <stdlib.h>

MemUndoRedoService* createMemUndoRedoService(MemUndoRedoRepo* repository) {
	MemUndoRedoService* service = (MemUndoRedoService*)malloc(sizeof(MemUndoRedoService));
	if (service == NULL) return NULL;

	service->repository = repository;
	return service;
}

void addMemUndoRedoService(MemUndoRedoService* service, MaterialsRepository* repository) {
	addMemUndoRedoRepo(service->repository, repository);
}

MaterialsRepository* getFromIndexMemUndoRedoService(MemUndoRedoService* service, int index) {
	return getFromIndexMemUndoRedoRepo(service->repository, index);
}

void setIndexDataMemUndoRedoService(MemUndoRedoService* service, MaterialsRepository* repository, int index) {
	setIndexDataMemUndoRedoRepo(service->repository, repository, index);
}

MaterialsRepository* undoMemUndoRedoService(MemUndoRedoService* service) {
	int index = getUndoIndexMemUndoRedoRepo(service->repository);
	if (index == 0) return NULL;
	setUndoIndexMemUndoRedoRepo(service->repository, index - 1);
	return getFromIndexMemUndoRedoRepo(service->repository, index - 1);
}

MaterialsRepository* redoMemUndoRedoService(MemUndoRedoService* service) {
	int index = getUndoIndexMemUndoRedoRepo(service->repository);
	if (index == getMaxIndexMemUndoRedoRepo(service->repository)) return NULL;
	setUndoIndexMemUndoRedoRepo(service->repository, index + 1);
	return getFromIndexMemUndoRedoRepo(service->repository, index + 1);
}

void destroyMemUndoRedoService(MemUndoRedoService* service) {
	destroyMemUndoRedoRepo(service->repository);
	free(service);
}
