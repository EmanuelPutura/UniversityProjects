#include "test_repository.h"
#include "materials_repository.h"
#include "material.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void testAddToRepo() {
	MaterialsRepository* repository = createMaterialsRepository();

	Material* m1 = createMaterial("Bread", "Kaufland", 20, "09/09/2009");
	Material* m2 = createMaterial("Pear Pie", "Lidl", 100, "11/07/2011");

	addMaterialToRepo(repository, m1);
	addMaterialToRepo(repository, m2);

	Material** data = getRepoData(repository);
	assert(equalMaterials(data[0], m1));

	destroyMaterialsRepository(repository);
}

void testCopyRepo() {
	MaterialsRepository* repository1 = createMaterialsRepository();
	
	Material* m1 = createMaterial("Bread", "Kaufland", 20, "09/09/2009");
	Material* m2 = createMaterial("Pear Pie", "Lidl", 100, "11/07/2011");

	addMaterialToRepo(repository1, m1);
	addMaterialToRepo(repository1, m2);

	MaterialsRepository* repository2 = copyMaterialsRepository(repository1);

	Material** data1 = getRepoData(repository1);
	Material** data2 = getRepoData(repository2);
	
	assert(equalMaterials(data1[0], data2[0]));
	assert(equalMaterials(data1[1], data2[1]));

	destroyMaterialsRepository(repository1);
	destroyMaterialsRepository(repository2);
}

void testGetLengthRepo() {
	MaterialsRepository* repository = createMaterialsRepository();

	Material* m1 = createMaterial("Bread", "Kaufland", 20, "09/09/2009");
	Material* m2 = createMaterial("Pear Pie", "Lidl", 100, "11/07/2011");

	addMaterialToRepo(repository, m1);
	addMaterialToRepo(repository, m2);

	assert(getRepoDataLength(repository) == 2);

	addMaterialToRepo(repository, copyMaterial(m1));
	assert(getRepoDataLength(repository) == 3);

	addMaterialToRepo(repository, copyMaterial(m2));
	assert(getRepoDataLength(repository) == 4);

	destroyMaterialsRepository(repository);
}

void updateRepo() {
	MaterialsRepository* repository = createMaterialsRepository();

	Material* m1 = createMaterial("Bread", "Kaufland", 20, "09/09/2009");
	Material* m2 = createMaterial("Pear Pie", "Lidl", 100, "11/07/2011");

	addMaterialToRepo(repository, m1);
	addMaterialToRepo(repository, m2);

	updateMaterialNameRepo(repository, 1, "Apple Pie");
	assert(!strcmp(getMaterialName(getRepoData(repository)[1]), "Apple Pie"));

	updateMaterialSupplierRepo(repository, 1, "Supplier Company");
	assert(!strcmp(getMaterialSupplier(getRepoData(repository)[1]), "Supplier Company"));

	Material** data = getRepoData(repository);

	destroyMaterialsRepository(repository);
}

void removeRepo() {
	MaterialsRepository* repository = createMaterialsRepository();

	Material* m1 = createMaterial("Bread", "Kaufland", 20, "09/09/2009");
	Material* m2 = createMaterial("Pear Pie", "Lidl", 100, "11/07/2011");

	addMaterialToRepo(repository, m1);
	addMaterialToRepo(repository, m2);
	removeMaterialFromRepo(repository, m1);

	Material** data = getRepoData(repository);
	assert(getRepoDataLength(repository) == 1);
	assert(equalMaterials(data[0], m2));

	destroyMaterialsRepository(repository);
}
