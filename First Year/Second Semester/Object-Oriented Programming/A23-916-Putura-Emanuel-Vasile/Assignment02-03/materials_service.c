#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "materials_service.h"
#include "validators.h"
#include "quick_sort.h"
#include "comparison_functionc.h"
#include "text_table.h"
#include "mementoDP_undoredo_service.h"

MaterialsService* createMaterialsService(MaterialsRepository* materials_repository, void* undoredo_service, bool cmd_service) {
	MaterialsService* materials_service = (MaterialsService*)malloc(sizeof(MaterialsService));
	if (materials_service == NULL) return NULL;

	materials_service->materials_repository = materials_repository;
	materials_service->undoredo_service = undoredo_service;
	materials_service->cmd_undoredo_service = cmd_service;

	return materials_service;
}

int addMaterialService(MaterialsService* materials_service, const char* name, const char* supplier, int* quantity, const char* expiration_date, bool ur_register) {
	Material* material = createMaterial(name, supplier, *quantity, expiration_date);
	if (material == NULL || !validateMaterial(material)) {
		destroyMaterial(material);
		return -1;
	}
	
	int index = getMaterialIndexRepo(materials_service->materials_repository, material);
	Material **data = getRepoData(materials_service->materials_repository);

	int new_quantity = 0;
	if (index != -1) {
		new_quantity = *quantity + *(getMaterialQuantity(data[index]));
		destroyMaterial(material);
		setMaterialQuantity(data[index], &new_quantity);
	}
	else addMaterialToRepo(materials_service->materials_repository, material);

	if (ur_register && !materials_service->cmd_undoredo_service) addMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository));
	
	if (ur_register && materials_service->cmd_undoredo_service) {
		const char* data[] = { name, supplier, expiration_date, name, supplier, expiration_date };
		char** args = (char**)malloc(6 * sizeof(char*));
		if (args == NULL) return -1;

		for (int i = 0; i < 6; ++i) {
			args[i] = (char*)malloc((strlen(data[i]) + 1) * sizeof(char));
			if (args[i] == NULL) return -1;
			strcpy(args[i], data[i]);
		}

		if (index == -1) {
			int* ur_quantity = (int*)malloc(sizeof(int));
			if (ur_quantity == NULL) return -1;
			*ur_quantity = *quantity;

			CRUFunction* func1 = createCRUFunction(&removeMaterialService, 5, materials_service, args[0], args[1], args[2], false);
			CRUFunction* func2 = createCRUFunction(&addMaterialService, 6, materials_service, args[3], args[4], ur_quantity, args[5], false);
			UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
			addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
			free(args);
		}
		else {
			int* p_quantity = (int*)malloc(sizeof(int));
			int* n_quantity = (int*)malloc(sizeof(int));
			if (p_quantity == NULL || n_quantity == NULL) return -1;

			*p_quantity = new_quantity - *quantity;
			*n_quantity = new_quantity;

			CRUFunction* func1 = createCRUFunction(&updateMaterialQuantityService, 6, materials_service, args[0], args[1], args[2], p_quantity, false);
			CRUFunction* func2 = createCRUFunction(&updateMaterialQuantityService, 6, materials_service, args[3], args[4], args[5], n_quantity, false);
			UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
			addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
			free(args);
		}
	}

	return 0;
}

void addDefaultMaterialsService(MaterialsService* materials_service) {
	bool ur_register = false;
	int quantity = 50;

	addMaterialService(materials_service, "Bread", "Auchan", &quantity, "07/04/2021", ur_register);
	quantity = 100;
	addMaterialService(materials_service, "Cookie", "Lidl", &quantity, "12/05/2021", ur_register);
	quantity = 10;
	addMaterialService(materials_service, "Cake", "Lidl", &quantity, "10/03/2021", ur_register);
	quantity = 100;
	addMaterialService(materials_service, "Biscuit", "Kaufland", &quantity, "09/02/2022", ur_register);
	quantity = 150;
	addMaterialService(materials_service, "Brownie", "Penny", &quantity, "10/04/2021", ur_register);
	quantity = 50;
	addMaterialService(materials_service, "Pear Pie", "La 2 pasi", &quantity, "07/03/2021", ur_register);
	quantity = 30;
	addMaterialService(materials_service, "Tart", "Auchan", &quantity, "11/11/2021", ur_register);
	quantity = 50;
	addMaterialService(materials_service, "Muffin", "Kaufland", &quantity, "12/12/2021", ur_register);
	quantity = 500;
	addMaterialService(materials_service, "Doughnut", "Kaufland", &quantity, "25/04/2020", ur_register);
	quantity = 40;
	addMaterialService(materials_service, "Apple Pie", "Selgros", &quantity, "25/01/2021", ur_register);

	if (!ur_register && !materials_service->cmd_undoredo_service) {
		destroyMaterialsRepository(getFromIndexMemUndoRedoService(materials_service->undoredo_service, 0));
		setIndexDataMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository), 0);
	}
}

char* stringToLowerService(MaterialsService* materials_service, const char* string) {
	char* converted_str = (char*)malloc(BUFSIZE * sizeof(char));
	if (converted_str == NULL) return NULL;

	for (int i = 0; string[i]; i++) {
		converted_str[i] = tolower(string[i]);
		converted_str[i + 1] = 0;
	}

	return converted_str;
}

char* getAllDataRepresentationService(MaterialsService* materials_service) {
	int length = getDataLengthService(materials_service);
	return getDataRepresentationService(materials_service, getRepoData(materials_service->materials_repository), length);
}

char* getDataRepresentationService(MaterialsService* materials_service, Material **data, int length) {
	if (length < 1) return NULL;
	return getTextTableService(materials_service, data, length);
}

char* getTextTableService(MaterialsService* materials_service, Material** data, int length) {
	TextTable* text_table = createTextTable(4);
	if (text_table == NULL) return NULL;

	addRowTextTable(text_table, true, 4, "NAME", "SUPPLIER", "QUANTITY", "EXPIRATION DATE");
	for (int i = 0; i < length; ++i) {
		char str_quantity[BUFSIZE], str_date[BUFSIZE];
		sprintf(str_quantity, "%d", *getMaterialQuantity(data[i]));
		dateToString(getMaterialExpirationDate(data[i]), str_date);
		addRowTextTable(text_table, false, 4, getMaterialName(data[i]), getMaterialSupplier(data[i]), str_quantity, str_date);
	}

	char* representation = getStringReprTextTable(text_table);
	destroyTextTable(text_table);
	return representation;
}

char* getRepoTextTableService(MaterialsService* materials_service) {
	Material** data = getRepoData(materials_service->materials_repository);
	return getTextTableService(materials_service, data, getRepoDataLength(materials_service->materials_repository));
}

int getDataLengthService(MaterialsService* materials_service) {
	return getRepoDataLength(materials_service->materials_repository);
}

int updateMaterialNameService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, const char* new_name, bool ur_register) {
	if (!strcmp(new_name, "")) return -1;
	Date* expiration_date = createDate(exp_date);
	if (expiration_date == NULL) return -1;
	if (!validateDate(expiration_date)) {
		destroyDate(expiration_date);
		return -1;
	}

	int index = getMaterialIndexByDataService(materials_service, name, supplier, expiration_date);
	destroyDate(expiration_date);

	int past_index = getMaterialIndexByDataService(materials_service, new_name, supplier, expiration_date);
	if (past_index != -1)
		return -1;

	if (index == -1) return -1;

	updateMaterialNameRepo(materials_service->materials_repository, index, new_name);
	if (ur_register && !materials_service->cmd_undoredo_service) addMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository));
	
	if (ur_register && materials_service->cmd_undoredo_service) {
		const char* data[] = { new_name, supplier, exp_date, name, name, supplier, exp_date, new_name };
		char** args = (char**)malloc(8 * sizeof(char*));
		if (args == NULL) return -1;

		for (int i = 0; i < 8; ++i) {
			args[i] = (char*)malloc((strlen(data[i]) + 1) * sizeof(char));
			if (args[i] == NULL) return -1;
			strcpy(args[i], data[i]);
		}

		CRUFunction* func1 = createCRUFunction(&updateMaterialNameService, 6, materials_service, args[0], args[1], args[2], args[3], false);
		CRUFunction* func2 = createCRUFunction(&updateMaterialNameService, 6, materials_service, args[4], args[5], args[6], args[7], false);
		UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
		addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
		free(args);
	}

	return 0;
}

int updateMaterialSupplierService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, const char* new_supplier, bool ur_register) {
	if (!strcmp(new_supplier, "")) return -1;
	Date* expiration_date = createDate(exp_date);
	if (expiration_date == NULL) return -1;
	if (!validateDate(expiration_date)) {
		destroyDate(expiration_date);
		return -1;
	}

	int index = getMaterialIndexByDataService(materials_service, name, supplier, expiration_date);
	destroyDate(expiration_date);
	
	int past_index = getMaterialIndexByDataService(materials_service, name, new_supplier, expiration_date);
	if (past_index != -1)
		return -1;

	if (index == -1) return -1;

	updateMaterialSupplierRepo(materials_service->materials_repository, index, new_supplier);
	if (ur_register && !materials_service->cmd_undoredo_service) addMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository));

	if (ur_register && materials_service->cmd_undoredo_service) {
		const char* data[] = { name, new_supplier, exp_date, supplier, name, supplier, exp_date, new_supplier };
		char** args = (char**)malloc(8 * sizeof(char*));
		if (args == NULL) return -1;

		for (int i = 0; i < 8; ++i) {
			args[i] = (char*)malloc((strlen(data[i]) + 1) * sizeof(char));
			if (args[i] == NULL) return -1;
			strcpy(args[i], data[i]);
		}

		CRUFunction* func1 = createCRUFunction(&updateMaterialSupplierService, 6, materials_service, args[0], args[1], args[2], args[3], false);
		CRUFunction* func2 = createCRUFunction(&updateMaterialSupplierService, 6, materials_service, args[4], args[5], args[6], args[7], false);
		UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
		addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
		free(args);
	}

	return 0;
}

int updateMaterialQuantityService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, int* new_quantity, bool ur_register) {
	if (*new_quantity <= 0) return -1;
	Date* expiration_date = createDate(exp_date);
	if (expiration_date == NULL) return -1;
	if (!validateDate(expiration_date)) {
		destroyDate(expiration_date);
		return -1;
	}

	int index = getMaterialIndexByDataService(materials_service, name, supplier, expiration_date);
	destroyDate(expiration_date);

	if (index == -1) return -1;
	
	int p_quantity = *getMaterialQuantity(getRepoData(materials_service->materials_repository)[index]);

	updateMaterialQuantityRepo(materials_service->materials_repository, index, new_quantity);	
	if (ur_register && !materials_service->cmd_undoredo_service) addMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository));

	if (ur_register && materials_service->cmd_undoredo_service) {
		const char* data[] = { name, supplier, exp_date, name, supplier, exp_date };
		char** args = (char**)malloc(6 * sizeof(char*));
		if (args == NULL) return -1;

		for (int i = 0; i < 6; ++i) {
			args[i] = (char*)malloc((strlen(data[i]) + 1) * sizeof(char));
			if (args[i] == NULL) return -1;
			strcpy(args[i], data[i]);
		}

		int* quantity = (int*)malloc(sizeof(int));
		int* n_quantity = (int*)malloc(sizeof(int));
		if (quantity == NULL || n_quantity == NULL) return -1;

		*quantity = p_quantity;
		*n_quantity = *new_quantity;

		CRUFunction* func1 = createCRUFunction(&updateMaterialQuantityService, 6, materials_service, args[0], args[1], args[2], quantity, false);
		CRUFunction* func2 = createCRUFunction(&updateMaterialQuantityService, 6, materials_service, args[3], args[4], args[5], n_quantity, false);
		UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
		addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
		free(args);
	}

	return 0;
}

int updateMaterialExpirationDateService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, const char* new_exp_date, bool ur_register) {
	Date* expiration_date = createDate(exp_date);
	if (expiration_date == NULL) return -1;
	if (!validateDate(expiration_date)) {
		destroyDate(expiration_date);
		return -1;
	}
	
	int index = getMaterialIndexByDataService(materials_service, name, supplier, expiration_date);
	destroyDate(expiration_date);
	
	Date* new_expiration_date = createDate(new_exp_date);
	if (new_expiration_date == NULL) return -1;
	if (!validateDate(new_expiration_date)) {
		destroyDate(new_expiration_date);
		return -1;
	}

	int past_index = getMaterialIndexByDataService(materials_service, name, supplier, new_expiration_date);
	destroyDate(new_expiration_date);

	if (past_index != -1)
		return -1;

	if (index == -1) return -1;

	updateMaterialExpirationDateRepo(materials_service->materials_repository, index, new_exp_date);
	if (ur_register && !materials_service->cmd_undoredo_service) addMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository));

	if (ur_register && materials_service->cmd_undoredo_service) {
		const char* data[] = { name, supplier, new_exp_date, exp_date, name, supplier, exp_date, new_exp_date };
		char** args = (char**)malloc(8 * sizeof(char*));
		if (args == NULL) return -1;

		for (int i = 0; i < 8; ++i) {
			args[i] = (char*)malloc((strlen(data[i]) + 1) * sizeof(char));
			if (args[i] == NULL) return -1;
			strcpy(args[i], data[i]);
		}

		CRUFunction* func1 = createCRUFunction(&updateMaterialExpirationDateService, 6, materials_service, args[0], args[1], args[2], args[3], false);
		CRUFunction* func2 = createCRUFunction(&updateMaterialExpirationDateService, 6, materials_service, args[4], args[5], args[6], args[7], false);
		UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
		addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
		free(args);
	}

	return 0;
}

int removeMaterialService(MaterialsService* materials_service, const char* name, const char* supplier, const char* expiration_date, bool ur_register) {
	Date* exp_date = createDate(expiration_date);
	if (exp_date == NULL) return -1;
	if (!validateDate(exp_date)) {
		destroyDate(exp_date);
		return -1;
	}
	
	
	int index = getMaterialIndexByDataService(materials_service, name, supplier, exp_date);
	if (index == -1)
	{
		destroyDate(exp_date);
		return -1;
	}
	Material* material = getRepoData(materials_service->materials_repository)[index];
	int p_quantity = *getMaterialQuantity(material);
	destroyDate(exp_date);

	int return_value = removeMaterialFromRepo(materials_service->materials_repository, material);
	if (ur_register && !materials_service->cmd_undoredo_service) addMemUndoRedoService(materials_service->undoredo_service, copyMaterialsRepository(materials_service->materials_repository));
	
	if (ur_register && materials_service->cmd_undoredo_service) {
		const char* data[] = { name, supplier, expiration_date, name, supplier, expiration_date };
		char** args = (char**)malloc(6 * sizeof(char*));
		if (args == NULL) return -1;

		for (int i = 0; i < 6; ++i) {
			args[i] = (char*)malloc((strlen(data[i]) + 1) * sizeof(char));
			if (args[i] == NULL) return -1;
			strcpy(args[i], data[i]);
		}

		int* quantity = (int*)malloc(sizeof(int));
		if (quantity == NULL) return -1;
		*quantity = p_quantity;

		CRUFunction* func1 = createCRUFunction(&addMaterialService, 6, materials_service, args[0], args[1], quantity, args[2], false);
		CRUFunction* func2 = createCRUFunction(&removeMaterialService, 5, materials_service, args[3], args[4], args[5], false);
		UndoRedoFunction* ur_function = createUndoRedoFunction(func1, func2);
		addCmdUndoRedoService(materials_service->undoredo_service, ur_function);
		free(args);
	}

	return return_value;
}

Material** findMaterialsPastExpDateService(MaterialsService* materials_service, char* reference_date, char* string, int* found_length) {
	Date* ref_date = createDate(reference_date);
	if (ref_date == NULL) return NULL;
	if (!validateDate(ref_date)) {
		destroyDate(ref_date);
		return NULL;
	}

	int length = getRepoDataLength(materials_service->materials_repository);
	if (length < 1) {
		if (ref_date != NULL) destroyDate(ref_date);
		return NULL;
	}

	*found_length = 0;
	bool converted = false;

	Material **data = getRepoData(materials_service->materials_repository);
	Material **found_data = (Material**)malloc(length * sizeof(Material*));
	if (found_data == NULL) {
		if (ref_date != NULL) destroyDate(ref_date);
		return NULL;
	}

	if (strcmp(string, "")) {
		string = stringToLowerService(materials_service, string);
		converted = true;
	}

	for (int i = 0; i < length; ++i)
		if (greaterDate(ref_date, getMaterialExpirationDate(data[i]))) {
			
			char* lower_name = stringToLowerService(materials_service, getMaterialName(data[i]));
			char* lower_supplier = stringToLowerService(materials_service, getMaterialSupplier(data[i]));

			if (!strcmp(string, "") || (strcmp(string, "") && (strstr(lower_name, string) || strstr(lower_supplier, string)))) {
				char exp_date[BUFSIZE];
				dateToString(getMaterialExpirationDate(data[i]), exp_date);
				found_data[*found_length] = createMaterial(getMaterialName(data[i]), getMaterialSupplier(data[i]), *(getMaterialQuantity(data[i])), exp_date);
				if (found_data[*found_length] == NULL) {
					if (ref_date != NULL) destroyDate(ref_date);
					free(lower_name);
					free(lower_supplier);
					return NULL;
				}
				*found_length += 1;
			}

			free(lower_name);
			free(lower_supplier);
		}
	if (converted) free(string);
	destroyDate(ref_date);

	return found_data;
}

Material** findAllMaterialsContainingString(MaterialsService* materials_service, char* string, int* found_length) {
	int length = getRepoDataLength(materials_service->materials_repository);
	if (length < 1) return NULL;

	*found_length = 0;
	bool converted = false;

	Material** data = getRepoData(materials_service->materials_repository);
	Material** found_data = (Material**)malloc(length * sizeof(Material*));
	if (found_data == NULL) return NULL;

	if (strcmp(string, "")) {
		string = stringToLowerService(materials_service, string);
		converted = true;
	}

	for (int i = 0; i < length; ++i) {
		char* lower_name = stringToLowerService(materials_service, getMaterialName(data[i]));
		char* lower_supplier = stringToLowerService(materials_service, getMaterialSupplier(data[i]));

		if (!strcmp(string, "") || (strcmp(string, "") && (strstr(lower_name, string) || strstr(lower_supplier, string)))) {
			char exp_date[BUFSIZE];
			dateToString(getMaterialExpirationDate(data[i]), exp_date);
			found_data[*found_length] = createMaterial(getMaterialName(data[i]), getMaterialSupplier(data[i]), *(getMaterialQuantity(data[i])), exp_date);
			if (found_data[*found_length] == NULL) {
				free(lower_name);
				free(lower_supplier);
				return NULL;
			}
			*found_length += 1;
		}

		free(lower_name);
		free(lower_supplier);
	}

	if (converted) free(string);

	return found_data;
}

Material** findMaterialsFromSupplierShortInSupply(MaterialsService* materials_service, const char* supplier, int quantity, int* found_length) {
	int length = getRepoDataLength(materials_service->materials_repository);
	if (length < 1) return NULL;

	*found_length = 0;

	Material** data = getRepoData(materials_service->materials_repository);
	Material** found_data = (Material**)malloc(length * sizeof(Material*));
	if (found_data == NULL) return NULL;

	for (int i = 0; i < length; ++i) {
		if (!strcmp(getMaterialSupplier(data[i]), supplier) && *getMaterialQuantity(data[i]) < quantity) {
			char exp_date[BUFSIZE];
			dateToString(getMaterialExpirationDate(data[i]), exp_date);
			found_data[*found_length] = createMaterial(getMaterialName(data[i]), getMaterialSupplier(data[i]), *(getMaterialQuantity(data[i])), exp_date);
			if (found_data[*found_length] == NULL) return NULL;
			*found_length += 1;
		}
	}
	return found_data;
}

Material** findOption8MaterialsService(MaterialsService* materials_service, char* string, int year, int* found_length) {
	int length = getRepoDataLength(materials_service->materials_repository);
	if (length < 1) return NULL;

	*found_length = 0;

	Material** data = getRepoData(materials_service->materials_repository);
	Material** found_data = (Material**)malloc(length * sizeof(Material*));
	if (found_data == NULL) return NULL;

	bool converted = false;

	if (strcmp(string, "")) {
		string = stringToLowerService(materials_service, string);
		converted = true;
	}

	for (int i = 0; i < length; ++i) {
		char* lower_name = stringToLowerService(materials_service, getMaterialName(data[i]));
		char* lower_supplier = stringToLowerService(materials_service, getMaterialSupplier(data[i]));

		if ((!strcmp(string, "") || (strcmp(string, "") && (strstr(lower_name, string) || strstr(lower_supplier, string)))) && \
						(getDateYear(getMaterialExpirationDate(data[i])) == year)) {
			char exp_date[BUFSIZE];
			dateToString(getMaterialExpirationDate(data[i]), exp_date);

			found_data[*found_length] = createMaterial(getMaterialName(data[i]), getMaterialSupplier(data[i]), *(getMaterialQuantity(data[i])), exp_date);
			if (found_data[*found_length] == NULL) {
				free(lower_name);
				free(lower_supplier);
				return NULL;
			}
			*found_length += 1;
		}

		free(lower_name);
		free(lower_supplier);
	}

	if (converted) free(string);

	return found_data;
}

char* getMaterialsStrPastExpDateService(MaterialsService* materials_service, char* reference_date, char* string, int* found_length) {
	Material** found_data = findMaterialsPastExpDateService(materials_service, reference_date, string, found_length);
	return getMaterialsStringService(materials_service, found_data, *found_length, "N", NULL, NULL, NULL);
}

char* getAllContainingStringSortedBySupplier(MaterialsService* materials_service, char* string, int* found_length) {
	Material** found_data = findAllMaterialsContainingString(materials_service, string, found_length);
	return getMaterialsStringService(materials_service, found_data, *found_length, "D", NULL, &alphaLessString, &getMaterialSupplier);
}

char* getMaterialsShortInSupplyStr(MaterialsService* materials_service, const char* supplier, const char* sorting_order, int quantity, int* found_length) {
	Material** found_data = findMaterialsFromSupplierShortInSupply(materials_service, supplier, quantity, found_length);
	return getMaterialsStringService(materials_service, found_data, *found_length, sorting_order, &greaterInteger, &lessInteger, &getMaterialQuantity);
}

char* getOption8MaterialString(MaterialsService* materials_service, char* string, int year, char* sorting_order, int* found_length) {
	Material** found_data = findOption8MaterialsService(materials_service, string, year, found_length);
	return getMaterialsStringService(materials_service, found_data, *found_length, sorting_order, &alphaGreaterString, &alphaLessString, &getMaterialName);
}

char* getMaterialsStringService(MaterialsService* materials_service, Material** data, int length, const char* sorting_order, bool (*greaterFunc)(void*, void*), \
																		bool (*lessFunc)(void*, void*), void* (*getFunc)(void*)) {
	bool (*comparisonFunc)(void*, void*) = NULL;
	bool not_compare = false;

	if (!strcmp(sorting_order, "A")) comparisonFunc = greaterFunc;
	else if (!strcmp(sorting_order, "D")) comparisonFunc = lessFunc;
	else if (!strcmp(sorting_order, "N")) not_compare = true;

	if (comparisonFunc == NULL && !not_compare) {
		for (int i = 0; i < length; ++i)
			destroyMaterial(data[i]);
		free(data);
		return NULL;
	}

	if (!not_compare) quickSort(data, 0, length - 1, comparisonFunc, getFunc, &swapMaterials);
	char* representation = getDataRepresentationService(materials_service, data, length);

	for (int i = 0; i < length; ++i)
		destroyMaterial(data[i]);
	free(data);

	return representation;
}

int getMaterialIndexByDataService(MaterialsService* materials_service, const char* name, const char* supplier, Date* expiration_date) {
	int length = getRepoDataLength(materials_service->materials_repository);
	Material** data = getRepoData(materials_service->materials_repository);

	for (int i = 0; i < length; ++i)
		if (equalMaterialsData(data[i], name, supplier, expiration_date)) return i;
	return -1;
}

int undoMaterialsService(MaterialsService* materials_service) {
	if (!materials_service->cmd_undoredo_service) {
		MaterialsRepository* new_repo = undoMemUndoRedoService(materials_service->undoredo_service);
		if (new_repo == NULL) return -1;
		destroyMaterialsRepository(materials_service->materials_repository);
		materials_service->materials_repository = copyMaterialsRepository(new_repo);
		return 0;
	}
	return undoCmdUndoRedoService(materials_service->undoredo_service);
}

int redoMaterialsService(MaterialsService* materials_service) {
	if (!materials_service->cmd_undoredo_service) {
		MaterialsRepository* new_repo = redoMemUndoRedoService(materials_service->undoredo_service);
		if (new_repo == NULL) return -1;
		destroyMaterialsRepository(materials_service->materials_repository);
		materials_service->materials_repository = copyMaterialsRepository(new_repo);
		return 0;
	}
	return redoCmdUndoRedoService(materials_service->undoredo_service);
}

void destroyMaterialsService(MaterialsService* materials_service) {
	destroyMaterialsRepository(materials_service->materials_repository);
	if (!materials_service->cmd_undoredo_service) destroyMemUndoRedoService(materials_service->undoredo_service);
	else destroyCmdUndoRedoService(materials_service->undoredo_service);
	free(materials_service);
}