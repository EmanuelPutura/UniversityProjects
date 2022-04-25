/*
*  Materials Service Module - implements the MaterialsService structure representing the application's materials service and its specific functions
*/

#pragma once

#include "materials_repository.h"
#include "mementoDP_undoredo_service.h"
#include "cmdDP_undoredo_service.h"
#include "material.h"
#include "date.h"

#include <stdarg.h>

/*
*  MaterialService Structure. Handles the application's materials service
*/
typedef struct {
	MaterialsRepository* materials_repository;
	void* undoredo_service;
	bool cmd_undoredo_service;
} MaterialsService;

/*
*  Creates a MaterialsService object
*  <param materials_repository> - pointer to a MaterialRepository object representing the attribute of the MaterialService object to be created
*  <returns> - a pointer to the newly created MaterialService object, or NULL if the object could not be created
*/
MaterialsService* createMaterialsService(MaterialsRepository* materials_repository, void* undoredo_service, bool cmd_service);

/*
*  Adds a material to the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of the string representing the name of the material to be added to the repository
*  <param supplier> - pointer to the first character of the string representing the supplier of the material to be added to the repository
*  <param quantity> - integer representing the quantity of the material to be added to the repository
*  <param expiration_date> - pointer to the first character of the string representing the expiration date of the material to be added to the repository
*/
int addMaterialService(MaterialsService* materials_service, const char* name, const char* supplier, int* quantity, const char* expiration_date, bool ur_register);

/*
*  Adds default materials to the repository
*  <param materials_service> - pointer to a MaterialsService object
*/
void addDefaultMaterialsService(MaterialsService* materials_service);

/*
*  Converts all the characters of a string to lowercase
*  <param materials_service> - pointer to a MaterialsService object
*  <param string> - pointer to the first character of the string to be converted
*  <returns> - pointer to the first character of the converted string
*/
char* stringToLowerService(MaterialsService* materials_service, const char* string);

/*
*  Gets the string representation of all the materials in the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <returns> - pointer to a char pointer, representing the address of the first element of an array of char pointers, each one of them being a pointer to the first
*  character of a material from the repository
*/
char* getAllDataRepresentationService(MaterialsService* materials_service);

/*
*  Gets the string representation of some materials
*  <param materials_service> - pointer to a MaterialsService object
*  <param data> - pointer to Material*, representing the address of the first element of an array of pointers to Material objects
*  <param length> - the length of the given data
*  <returns> - pointer to a char pointer, representing the address of the first element of an array of char pointers, each one of them being a pointer to the first
*  character of a material from the given ones
*/
char* getDataRepresentationService(MaterialsService* materials_service, Material **data, int length);

/*
*  Gets a TextTable object for the string representation of all the Material objects stores in the repository
*/
char* getTextTableService(MaterialsService* materials_service, Material** data, int length);

char* getRepoTextTableService(MaterialsService* materials_service);

/*
*  Gets the number of all the materials in the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <returns> - the number of all the materials in the repository
*/
int getDataLengthService(MaterialsService* materials_service);

/*
*  Updates the name of a material from the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of a string representing the name of the material to be updated
*  <param supplier> - pointer to the first character of a string representing the supplier of the material to be updated
*  <param exp_date> - pointer to the first character of a string representing the expiration date of the material to be updated (format is DD/MM/YY)
*  <param new_name> - pointer to the first character of a string representing the new name of the material to be updated
	<returns> - zero if the update succeeded, -1 else
*/
int updateMaterialNameService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, const char* new_name, bool ur_register);

/*
*  Updates the supplier of a material from the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of a string representing the name of the material to be updated
*  <param supplier> - pointer to the first character of a string representing the supplier of the material to be updated
*  <param exp_date> - pointer to the first character of a string representing the expiration date of the material to be updated (format is DD/MM/YY)
*  <param new_supplier> - pointer to the first character of a string representing the new supplier of the material to be updated
	<returns> - zero if the update succeeded, -1 else
*/
int updateMaterialSupplierService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, const char* new_supplier, bool ur_register);

/*
*  Updates the quantity of a material from the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of a string representing the name of the material to be updated
*  <param supplier> - pointer to the first character of a string representing the supplier of the material to be updated
*  <param exp_date> - pointer to the first character of a string representing the expiration date of the material to be updated (format is DD/MM/YY)
*  <param new_quantity> - integer, the new quantity of the material
	<returns> - zero if the update succeeded, -1 else
*/
int updateMaterialQuantityService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, int* new_quantity, bool ur_register);

/*
*  Updates the expiration date of a material from the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of a string representing the name of the material to be updated
*  <param supplier> - pointer to the first character of a string representing the supplier of the material to be updated
*  <param exp_date> - pointer to the first character of a string representing the expiration date of the material to be updated (format is DD/MM/YY)
*  <param new_exp_date> - pointer to the first character of a string representing the new expiration date of the material to be updated
	<returns> - zero if the update succeeded, -1 else
*/
int updateMaterialExpirationDateService(MaterialsService* materials_service, const char* name, const char* supplier, const char* exp_date, const char* new_exp_date, bool ur_register);

/*
*  Removes a material from the repository
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of a string representing the name of the material to be removed
*  <param supplier> - pointer to the first character of a string representing the supplier of the material to be removed
*  <param expiration_date> - pointer to the first character of a string representing the expiration date of the material to be removed (format is DD/MM/YY)
*/
int removeMaterialService(MaterialsService* materials_service, const char* name, const char* supplier, const char* expiration_date, bool ur_register);

/*
*  Finds all the materials in the repository past their expiration date and containing a given string in their material name/supplier name
*  <param materials_service> - pointer to a MaterialsService object
*  <param reference_date> - pointer to the first character of a string representing the reference date
*  <param string> - pointer to the first character of the string that must be contained in the material name/supplier name
*  <param expiration_date> - pointer to the first character of the expiration date (format is DD/MM/YY)
*/
Material** findMaterialsPastExpDateService(MaterialsService* materials_service, char* reference_date, char* string, int* found_length);

/*
*  Finds the Material objects containing a given string
*/
Material** findAllMaterialsContainingString(MaterialsService* materials_service, char* string, int* found_length);

/*
*  Finds the Material objects for the 8th functionality
*/
Material** findOption8MaterialsService(MaterialsService* materials_service, char* string, int year, int* found_length);

/*
*  Gets string representation of the Material objects containg a string, past their expiration date
*/
char* getMaterialsStrPastExpDateService(MaterialsService* materials_service, char* reference_date, char* string, int* found_length);

/*
*  Gets string representation of the Material objects short in supply, sorted
*/
char* getMaterialsShortInSupplyStr(MaterialsService* materials_service, const char* supplier, const char* sorting_order, int quantity, int* found_length);

/*
*  Gets string representation of the Material objects found for the 8th functionality
*/
char* getOption8MaterialString(MaterialsService* materials_service, char* string, int year, char* sorting_order, int* found_length);

/*
*  Gets string representation of the Material objects containg a string, sorted
*/
char* getMaterialsStringService(MaterialsService* materials_service, Material** data, int length, const char* sorting_order, bool (*greaterFunc)(void*, void*), \
																						bool (*lessFunc)(void*, void*), void* (*getFunc)(void*));

/*
*  Gets the index of a material from the repository, based on the material's data
*  <param materials_service> - pointer to a MaterialsService object
*  <param name> - pointer to the first character of the name to be checked
*  <param supplier> - pointer to the first character of the supplier to be checked
*  <param expiration_date> - pointer to a Date object to be checked
*/
int getMaterialIndexByDataService(MaterialsService* materials_service, const char* name, const char* supplier, Date* expiration_date);

/*
*  Performs an undo operation
*/
int undoMaterialsService(MaterialsService* materials_service);

/*
*  Performs a redo operation
*/
int redoMaterialsService(MaterialsService* materials_service);

/*
*  Gets all containig strings objects sorted by supplier
*/
char* getAllContainingStringSortedBySupplier(MaterialsService* materials_service, char* string, int* found_length);

/*
*  Free the memory allocated for a MaterialsService object
*  <param materials_service> - pointer to a MaterialsService object
*/
void destroyMaterialsService(MaterialsService* materials_service);