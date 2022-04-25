/*
*  Materials Repository Module - implements the MaterialRepository structure representing the application's repository and its specific functionalities
*/

#pragma once
#include "material.h"
#include "dynamic_array.h"
#include "date.h"

#define ARRAYCAPACITY 100  // the dynamic array default capacity

/*
*  MaterialsRepository struct. Handles the application's Material data
*/
typedef struct {
	DynamicArray* array;
} MaterialsRepository;

/*
*  Creates a MaterialsRepository object
*  <returns> - the created MaterialsRepository object
*/
MaterialsRepository* createMaterialsRepository();

/*
*  Copies the attributes of a MaterialsRepository object to another one
*/
MaterialsRepository* copyMaterialsRepository(MaterialsRepository* materials_repository);

/*
*  Adds a material to the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param material> - pointer to a Material object to be added
*/
void addMaterialToRepo(MaterialsRepository* materials_repository, Material* material);

/*
*  Gets the index of a material from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param material> - pointer to a Material object to be searched for
*  <returns> - an integer representing the found index or -1 if the material was not found in the repository
*/
int getMaterialIndexRepo(MaterialsRepository* materials_repository, Material* material);

/*
*  Gets the repository data
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <returns> - pointer to the first Material object from the repository data
*/
Material **getRepoData(MaterialsRepository* materials_repository);

/*
*  Gets the length of the data from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <returns> - a positive integer representing the length of the data from the repository
*/
int getRepoDataLength(MaterialsRepository* materials_repository);

/*
*  Updates the name of a material from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param index> - positive integer (valid one) representing the index of the material to be updated
*  <param new_name> - pointer to the first character of the new name of the material
*/
void updateMaterialNameRepo(MaterialsRepository* materials_repository, int index, const char* new_name);

/*
*  Updates the supplier of a material from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param index> - positive integer (valid one) representing the index of the material to be updated
*  <param new_supplier> - pointer to the first character of the new supplier of the material
*/
void updateMaterialSupplierRepo(MaterialsRepository* materials_repository, int index, const char* new_supplier);

/*
*  Updates the quantity of a material from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param index> - positive integer (valid one) representing the index of the material to be updated
*  <param new_quantity> - pointer to integer representing the new material quantity
*/
void updateMaterialQuantityRepo(MaterialsRepository* materials_repository, int index, int* new_quantity);

/*
*  Updates the expiration date of a material from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param index> - positive integer (valid one) representing the index of the material to be updated
*  <param new_exp_date> - pointer to the first character of the new expiration date of the material
*/
void updateMaterialExpirationDateRepo(MaterialsRepository* materials_repository, int index, const char* new_exp_date);

/*
*  Removes a material from the repository
*  <param materials_repository> - pointer to a MaterialsRepository object
*  <param material> - pointer to a Material object to be removed from the repository
*/
int removeMaterialFromRepo(MaterialsRepository* materials_repository, Material* material);

/*
*  Checks if two MaterialsRepository objects are equal
*/
bool equalMaterialsRepository(MaterialsRepository* materials_repository1, MaterialsRepository* materials_repository2);

/*
*  Frees the memory allocated for a MaterialsRepository object
*  <param materials_repository> - pointer to a MaterialsRepository object
*/
void destroyMaterialsRepository(MaterialsRepository* materials_repository);
