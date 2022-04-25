#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "material.h"

Material* createMaterial(const char* name, const char* supplier, int quantity, const char* expiration_date) {
	Material* material = (Material*)malloc(sizeof(Material));
	if (material == NULL) return NULL;
	
	material->name = (char*)malloc(BUFSIZE * sizeof(char));
	if (material->name == NULL) return NULL;
	strcpy(material->name, name);

	material->supplier = (char*)malloc(BUFSIZE * sizeof(char));
	if (material->supplier == NULL) return NULL;
	strcpy(material->supplier, supplier);
	
	material->quantity = quantity;
	material->expiration_date = createDate(expiration_date);
	if (material->expiration_date == NULL) return NULL;

	return material;
}

Material* copyMaterial(Material* material) {
	char str_date[BUFSIZE];
	dateToString(material->expiration_date, str_date);
	return createMaterial(material->name, material->supplier, material->quantity, str_date);
}

char* getMaterialName(Material* material) {
	return material->name;
}

char* getMaterialSupplier(Material* material) {
	return material->supplier;
}

int* getMaterialQuantity(Material* material) {
	return &(material->quantity);
}

Date* getMaterialExpirationDate(Material* material) {
	return material->expiration_date;
}

void setMaterialName(Material* material, const char* name) {
	strcpy(material->name, name);
}

void setMaterialSupplier(Material* material, const char* supplier) {
	strcpy(material->supplier, supplier);
}

void setMaterialQuantity(Material* material, const int* quantity) {
	material->quantity = *quantity;
}

void setMaterialExpirationDate(Material* material, const char* expiration_date) {
	Date* exp_date = createDate(expiration_date);

	setDateDay(material->expiration_date, getDateDay(exp_date));
	setDateMonth(material->expiration_date, getDateMonth(exp_date));
	setDateYear(material->expiration_date, getDateYear(exp_date));

	destroyDate(exp_date);
}

void materialToString(Material* material, char* string_representation) {
	strcpy(string_representation, "Material: name - ");
	strcpy(string_representation + strlen(string_representation), material->name);
	strcpy(string_representation + strlen(string_representation), ", supplier - ");
	strcpy(string_representation + strlen(string_representation), material->supplier);
	strcpy(string_representation + strlen(string_representation), ", quantity - ");
	sprintf(string_representation + strlen(string_representation), "%d, exp_date - ", material->quantity);
	dateToString(material->expiration_date, string_representation + strlen(string_representation));
}

bool equalMaterials(Material* material1, Material* material2) {
	return !strcmp(material1->name, material2->name) && !strcmp(material1->supplier, material2->supplier)
		&& equalDates(material1->expiration_date, material2->expiration_date);
}

bool equalMaterialsData(Material* material, const char* name, const char* supplier, Date* expiration_date) {
	return !strcmp(material->name, name) && !strcmp(material->supplier, supplier)
		&& equalDates(material->expiration_date, expiration_date);
}

void swapMaterials(Material* material1, Material* material2) {
	char name[BUFSIZE], supplier[BUFSIZE];
	int quantity = material1->quantity;

	strcpy(name, material1->name);
	strcpy(supplier, material1->supplier);
	
	swapDates(material1->expiration_date, material2->expiration_date);
	
	material1->quantity = material2->quantity;
	material2->quantity = quantity;

	strcpy(material1->name, material2->name);
	strcpy(material2->name, name);

	strcpy(material1->supplier, material2->supplier);
	strcpy(material2->supplier, supplier);
}

void destroyMaterial(Material* material) {
	free(material->name);
	free(material->supplier);
	destroyDate(material->expiration_date);
	free(material);
}