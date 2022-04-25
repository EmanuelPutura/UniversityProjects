#include "cmdDP_undoredo_service.h"

#include <stdlib.h>

CmdUndoRedoService* createCmdUndoRedoService(CmdUndoRedoRepo* repository) {
	CmdUndoRedoService* service = (CmdUndoRedoService*)malloc(sizeof(CmdUndoRedoService));
	if (service == NULL) return NULL;

	service->repository = repository;
	return service;
}

void addCmdUndoRedoService(CmdUndoRedoService* service, UndoRedoFunction* function) {
	addCmdUndoRedoRepo(service->repository, function);
}

UndoRedoFunction* getFromIndexCmdUndoRedoService(CmdUndoRedoService* service, int index) {
	return getFromIndexCmdUndoRedoRepo(service->repository, index);
}

void setIndexDataCmdUndoRedoService(CmdUndoRedoService* service, UndoRedoFunction* function, int index) {
	setIndexDataCmdUndoRedoRepo(service->repository, function, index);
}

int undoCmdUndoRedoService(CmdUndoRedoService* service) {
	int index = getUndoIndexCmdUndoRedoRepo(service->repository);
	if (index == -1) return -1;
	undoFunction(getFromIndexCmdUndoRedoRepo(service->repository, index));
	setUndoIndexCmdUndoRedoRepo(service->repository, index - 1);
	return 0;
}

int redoCmdUndoRedoService(CmdUndoRedoService* service) {
	int index = getUndoIndexCmdUndoRedoRepo(service->repository);
	if ((index + 1) == getLengthCmdUndoRedoRepo(service->repository)) return -1;
	setUndoIndexCmdUndoRedoRepo(service->repository, index + 1);
	redoFunction(getFromIndexCmdUndoRedoRepo(service->repository, index + 1));
	return 0;
}

void destroyCmdUndoRedoService(CmdUndoRedoService* service) {
	destroyCmdUndoRedoRepo(service->repository);
	free(service);
}
