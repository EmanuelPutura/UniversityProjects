/*
* "Bread'n Bagel" Bakery Application
* - Emanuel-Vasile Putura
* 
*  This is the main application module
*/

#include "materials_repository.h"
#include "mementoDP_undoredo_repo.h"
#include "cmdDP_undoredo_repo.h"
#include "quick_sort.h"
#include "test_all.h"
#include "materials_service.h"
#include "mementoDP_undoredo_service.h"
#include "cmdDP_undoredo_service.h"
#include "consoleUI.h"

#include <crtdbg.h>
#include <stdio.h>

int main() {
	testAll();

	MaterialsRepository* materials_repository = createMaterialsRepository();
	
	// MemUndoRedoRepo* mem_undoredo_repo = createMemUndoRedoRepo();
	// MemUndoRedoService* mem_undoredo_service = createMemUndoRedoService(mem_undoredo_repo);
	
	CmdUndoRedoRepo* cmd_undoredo_repo = createCmdUndoRedoRepo();
	CmdUndoRedoService* cmd_undoredo_service = createCmdUndoRedoService(cmd_undoredo_repo);

	// MaterialsService* materials_service = createMaterialsService(materials_repository, mem_undoredo_service, false);
	MaterialsService* materials_service = createMaterialsService(materials_repository, cmd_undoredo_service, true);
	
	ConsoleUI* consoleUI = createConsoleUI(materials_service);
	runMenuUI(consoleUI);
	destroyConsoleUI(consoleUI);
	
	int r = _CrtDumpMemoryLeaks();
	printf("Memory Leaks: %d\n", r);

	return 0;
}