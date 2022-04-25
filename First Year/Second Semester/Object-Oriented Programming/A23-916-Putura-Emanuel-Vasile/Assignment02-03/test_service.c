#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "material.h"
#include "test_service.h"
#include "materials_service.h"
#include "materials_repository.h"
#include "cmdDP_undoredo_repo.h"
#include "cmdDP_undoredo_service.h"

void testFindAllMaterialsContainingStringService() {
	int n = 7;
	CmdUndoRedoRepo* cmdr = createCmdUndoRedoRepo();
	CmdUndoRedoService* cmds = createCmdUndoRedoService(cmdr);
	MaterialsRepository* mr = createMaterialsRepository();
	MaterialsService* ms = createMaterialsService(mr, cmds, true);

	char* names[] = { "Bread", "Donnut", "Muffin", "Apple Pie", "Pie", "Pear Pie", "Croissant" };
	char* suppliers[] = { "Kaufland", "Lidl", "Auchan", "Auchan", "Penny", "La 2 pasi", "Lidl" };
	int quantities[] = { 10, 20, 10, 5, 9, 100, 35 };
	char* dates[] = { "10/10/2021", "12/10/2021", "09/07/2020", "10/10/2001", "11/12/2031", "15/10/2003", "25/01/2001" };

	for (int i = 0; i < n; ++i)
		addMaterialService(ms, names[i], suppliers[i], quantities + i, dates[i], true);

	int length = 0;
	Material** farr = findAllMaterialsContainingString(ms, "pi", &length);
	
	assert(length == 3);
	
	destroyMaterialsService(ms);

	for (int i = 0; i < length; ++i)
		destroyMaterial(farr[i]);
	free(farr);
}

void testAddService() {
	CmdUndoRedoRepo* cmdr = createCmdUndoRedoRepo();
	CmdUndoRedoService* cmds = createCmdUndoRedoService(cmdr);
	MaterialsRepository* mr = createMaterialsRepository();
	MaterialsService* ms = createMaterialsService(mr, cmds, true);

	int q = 50;
	addMaterialService(ms, "Bread", "Kaufland", &q, "09/09/2009", true);
	int length = 0;
	Material** farr = findAllMaterialsContainingString(ms, "Bread", &length);
	assert(length == 1);

	destroyMaterialsService(ms);
	destroyMaterial(farr[0]);
	free(farr);
}

void testMemUndoRedoService() {
	MemUndoRedoRepo* cmdr = createMemUndoRedoRepo();
	MemUndoRedoService* cmds = createMemUndoRedoService(cmdr);
	MaterialsRepository* mr = createMaterialsRepository();
	MaterialsService* ms = createMaterialsService(mr, cmds, false);

	int q = 50;
	addMaterialService(ms, "Bread", "Kaufland", &q, "09/09/2009", true);
	addMaterialService(ms, "Bread", "Lidl", &q, "09/09/2009", true);
	undoMaterialsService(ms);
	int length = 0;
	Material** farr = findAllMaterialsContainingString(ms, "Bread", &length);
	assert(length == 1);

	destroyMaterial(farr[0]);
	free(farr);

	redoMaterialsService(ms);
	length = 0;
	farr = findAllMaterialsContainingString(ms, "Bread", &length);
	assert(length == 2);

	destroyMaterialsService(ms);
	destroyMaterial(farr[0]);
	destroyMaterial(farr[1]);
	free(farr);
}

void testUpdateService() {
	MemUndoRedoRepo* cmdr = createMemUndoRedoRepo();
	MemUndoRedoService* cmds = createMemUndoRedoService(cmdr);
	MaterialsRepository* mr = createMaterialsRepository();
	MaterialsService* ms = createMaterialsService(mr, cmds, false);

	int q = 50;
	addMaterialService(ms, "Bread", "Kaufland", &q, "09/09/2009", true);
	addMaterialService(ms, "Bread", "Lidl", &q, "09/09/2009", true);
	updateMaterialNameService(ms, "Bread", "Lidl", "09/09/2009", "Donnut", true);
	int length = 0;
	Material** farr = findAllMaterialsContainingString(ms, "Donnut", &length);
	assert(length == 1);

	destroyMaterialsService(ms);
	destroyMaterial(farr[0]);
	free(farr);
}

void testCmdUndoRedoService() {
	CmdUndoRedoRepo* cmdr = createCmdUndoRedoRepo();
	CmdUndoRedoService* cmds = createCmdUndoRedoService(cmdr);
	MaterialsRepository* mr = createMaterialsRepository();
	MaterialsService* ms = createMaterialsService(mr, cmds, true);

	int q = 50;
	addMaterialService(ms, "Bread", "Kaufland", &q, "09/09/2009", true);
	addMaterialService(ms, "Bread", "Lidl", &q, "09/09/2009", true);
	undoMaterialsService(ms);
	int length = 0;
	Material** farr = findAllMaterialsContainingString(ms, "Bread", &length);
	assert(length == 1);

	destroyMaterial(farr[0]);
	free(farr);

	redoMaterialsService(ms);
	length = 0;
	farr = findAllMaterialsContainingString(ms, "Bread", &length);
	assert(length == 2);

	undoMaterialsService(ms);
	assert(getRepoDataLength(ms->materials_repository) == 1);

	undoMaterialsService(ms);
	assert(getRepoDataLength(ms->materials_repository) == 0);

	redoMaterialsService(ms);
	assert(getRepoDataLength(ms->materials_repository) == 1);

	redoMaterialsService(ms);
	assert(getRepoDataLength(ms->materials_repository) == 2);

	addMaterialService(ms, "Pie", "La 2 pasi", &q, "09/09/2020", true);
	undoMaterialsService(ms);
	assert(getRepoDataLength(ms->materials_repository) == 2);

	assert(redoMaterialsService(ms) == 0);

	q = 100;
	updateMaterialQuantityService(ms, "Bread", "Lidl", "09/09/2009", &q, true);

	assert(redoMaterialsService(ms) == -1);

	Material** data = getRepoData(ms->materials_repository);
	assert(*getMaterialQuantity(data[1]) == 100);
	
	q = 1000;
	updateMaterialQuantityService(ms, "Bread", "Lidl", "09/09/2009", &q, true);

	data = getRepoData(ms->materials_repository);
	assert(*getMaterialQuantity(data[1]) == 1000);

	undoMaterialsService(ms);
	assert(*getMaterialQuantity(data[1]) == 100);

	undoMaterialsService(ms);
	assert(*getMaterialQuantity(data[1]) == 50);

	redoMaterialsService(ms);
	assert(*getMaterialQuantity(data[1]) == 100);

	redoMaterialsService(ms);
	assert(*getMaterialQuantity(data[1]) == 1000);

	destroyMaterialsService(ms);
	destroyMaterial(farr[0]);
	destroyMaterial(farr[1]);
	free(farr);
}

void testRemoveService() {
	MemUndoRedoRepo* cmdr = createMemUndoRedoRepo();
	MemUndoRedoService* cmds = createMemUndoRedoService(cmdr);
	MaterialsRepository* mr = createMaterialsRepository();
	MaterialsService* ms = createMaterialsService(mr, cmds, false);

	int q = 50;
	addMaterialService(ms, "Bread", "Kaufland", &q, "09/09/2009", true);
	addMaterialService(ms, "Bread", "Lidl", &q, "09/09/2009", true);
	removeMaterialService(ms, "Bread", "Lidl", "09/09/2009", true);
	int length = 0;
	Material** farr = findAllMaterialsContainingString(ms, "Bread", &length);
	assert(length == 1);

	destroyMaterialsService(ms);
	destroyMaterial(farr[0]);
	free(farr);
}
