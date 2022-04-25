/*
*  Material Module - implements a Material structure and its specific functions
*/

#pragma once

#include "date.h"

#ifndef BUFSIZE
#define BUFSIZE 100 // constant representing a string maximum buffer size
#endif

/*
*  Material structure. Handles materials
*/
typedef struct {
	char* name, * supplier;
	int quantity;
	Date* expiration_date;
} Material;

/*
*  Creates a material object
*  <param name> - pointer to the first character of the material's name
*  <param supplier> - pointer to the first character of the material's supplier
*  <param quantity> - integer, the material's quantity
*  <param expiration_date> - pointer to the first character of the string representation of the material's expiration date (format DD/MM/YY)
*  <returns> - pointer to the newly created Material object, or NULL if the object could not be created
*/
Material* createMaterial(const char* name, const char* supplier, int quantity, const char* expiration_date);

/*
*  Copies the attributes of a Material object to another one
*/
Material* copyMaterial(Material* material);

/*
*  Gets the name of a material
*  <param material> - pointer to a Material object
*  <returns> - pointer to the first character of the name of the given material
*/
char* getMaterialName(Material* material);

/*
*  Gets the supplier of a material
*  <param material> - pointer to a Material object
*  <returns> - pointer to the first character of the supplier of the given material
*/
char* getMaterialSupplier(Material* material);

/*
*  Gets the quantity of a material
*  <param material> - pointer to a Material object
*  <returns> - integer, the quantity of the given material
*/
int* getMaterialQuantity(Material* material);

/*
*  Gets the expiration date of a material
*  <param material> - pointer to a Material object
*  <returns> - pointer to the expiration date of the given material
*/
Date* getMaterialExpirationDate(Material* material);

/*
*  Sets a material's name
*  <param material> - pointer to a Material object
*  <param name> - pointer to the first character of the material's new name
*/
void setMaterialName(Material* material, const char* name);

/*
*  Sets a material's supplier
*  <param material> - pointer to a Material object
*  <param supplier> - pointer to the first character of the material's new supplier
*/
void setMaterialSupplier(Material* material, const char* supplier);

/*
*  Sets a material's quantity
*  <param material> - pointer to a Material object
*  <param quantity> - integer, the material's new quantity
*/
void setMaterialQuantity(Material* material, const int* quantity);

/*
*  Sets a material's expiration date
*  <param material> - pointer to a Material object 
*  <param expiration_date> - pointer to the first character of the string representation of the material's new expiration date (format DD/MM/YY)
*/
void setMaterialExpirationDate(Material* material, const char* expiration_date);

/*
*  Gets the string representation of a material
*  <param material> - pointer to a Material object
*  <param string_representation> - output parameter, pointer to the first character of the string representation of the given material
*/
void materialToString(Material* material, char* string_representation);

/*
*  Checks if two materials are equal. Two materials are equal if and only if they have the same name, supplier and expiration date
*  <param material1> - pointer to a Material object, the first material
*  <param material2> - pointer to a Material object, the second material
*  <returns> - true if equal, false else
*/
bool equalMaterials(Material* material1, Material* material2);

/*
*  Checks if the attributes of a material is equal to some given data
*  <param material> - pointer to a Material object
*  <param name> - pointer to the first character of the name to be checked
*  <param supplier> - pointer to the first character of the supplier to be checked
*  <param expiration_date> - pointer to a Date object to be checked
*  <returns> - true if equal, false else
*/
bool equalMaterialsData(Material* material, const char* name, const char* supplier, Date* expiration_date);

/*
*  Swaps two Material objects
*/
void swapMaterials(Material* material1, Material* material2);

/*
*  Frees the memory allocated for a Material object
*  <param material> - pointer to a Material object
*/
void destroyMaterial(Material* material);