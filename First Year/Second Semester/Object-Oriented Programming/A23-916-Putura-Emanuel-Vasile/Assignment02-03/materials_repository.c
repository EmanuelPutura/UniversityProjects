#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materials_repository.h"

MaterialsRepository* createMaterialsRepository() {
	MaterialsRepository* materials_repository = (MaterialsRepository*)malloc(sizeof(MaterialsRepository));
	if (materials_repository == NULL) return NULL;

	materials_repository->array = createDynamicArray(ARRAYCAPACITY);
	if (materials_repository->array == NULL) return NULL;

	return materials_repository;
}

MaterialsRepository* copyMaterialsRepository(MaterialsRepository* materials_repository) {
	MaterialsRepository* new_repo = createMaterialsRepository();
	destroyDynamicArray(new_repo->array, NULL);
	new_repo->array = copyDynamicArray(materials_repository->array, &copyMaterial);
	return new_repo;
}

void addMaterialToRepo(MaterialsRepository* materials_repository, Material* material) {
	addDA(materials_repository->array, material);
}

int getMaterialIndexRepo(MaterialsRepository* materials_repository, Material* material) {
	return getIndexDA(materials_repository->array, material, &equalMaterials);
}

Material **getRepoData(MaterialsRepository* materials_repository) {
	return (Material**)getDataDA(materials_repository->array);
}

int getRepoDataLength(MaterialsRepository* materials_repository) {
	return getSizeDA(materials_repository->array);
}

void updateMaterialNameRepo(MaterialsRepository* materials_repository, int index, const char* new_name) {
	updateDA(materials_repository->array, index, &setMaterialName, new_name);
}

void updateMaterialSupplierRepo(MaterialsRepository* materials_repository, int index, const char* new_supplier) {
	updateDA(materials_repository->array, index, &setMaterialSupplier, new_supplier);
}

void updateMaterialQuantityRepo(MaterialsRepository* materials_repository, int index, int* new_quantity) {
	updateDA(materials_repository->array, index, &setMaterialQuantity, new_quantity);
}

void updateMaterialExpirationDateRepo(MaterialsRepository* materials_repository, int index, const char* new_exp_date) {
	updateDA(materials_repository->array, index, &setMaterialExpirationDate, new_exp_date);
}

int removeMaterialFromRepo(MaterialsRepository* materials_repository, Material* material) {
	return removeDA(materials_repository->array, material, &destroyMaterial, &equalMaterials);
}

bool equalMaterialsRepository(MaterialsRepository* materials_repository1, MaterialsRepository* materials_repository2) {
	Material **data1 = (Material**)getDataDA(materials_repository1->array), **data2 = (Material**)getDataDA(materials_repository2->array);
	if (getSizeDA(materials_repository1->array) != getSizeDA(materials_repository2->array)) return false;
	int length = getSizeDA(materials_repository1->array);

	for (int i = 0; i < length; ++i)
		if (!equalMaterials(data1[i], data2[i])) return false;
	return true;
}

void destroyMaterialsRepository(MaterialsRepository* materials_repository) {
	destroyDynamicArray(materials_repository->array, &destroyMaterial);
	free(materials_repository);
}