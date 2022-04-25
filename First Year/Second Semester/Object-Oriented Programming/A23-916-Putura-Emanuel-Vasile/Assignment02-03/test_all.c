#include "test_domain.h"
#include "test_tools.h"
#include "test_service.h"
#include "test_repository.h"
#include "test_validators.h"

void testAllDomain() {
	testCreateMaterial();
	testMaterialToString();
	testEqualMaterials();
	testEqualMaterialsData();
	testCreateDate();
	testGetDayFromString();
	testGetMonthFromString();
	testGetYearFromString();
	testLeapDateYear();
	testEqualDates();
	testCreateDynamicArray();
	testAddDA();
	testResizeDA();
	testGetIndexDA();
	testGetSizeDA();
	testRemoveDA();
	testQuickSort();
}

void testAllService() {
	testFindAllMaterialsContainingStringService();
	testAddService();
	testMemUndoRedoService();
	testCmdUndoRedoService();
	testUpdateService();
	testRemoveService();
}

void testAllMaterialsRepository() {
	testAddToRepo();
	testCopyRepo();
	testGetLengthRepo();
	updateRepo();
	removeRepo();
}

void testAllValidators() {
	testValidateMaterial();
	testValidateDate();
}

void testAll() {
	testAllDomain();
	testAllService();
	testAllMaterialsRepository();
	testAllValidators();
}