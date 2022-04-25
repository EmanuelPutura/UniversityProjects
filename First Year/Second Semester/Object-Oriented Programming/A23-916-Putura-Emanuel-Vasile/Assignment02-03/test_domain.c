#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "material.h"
#include "date.h"
#include "dynamic_array.h"

void testCreateMaterial() {
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");
	Date* d1 = createDate("10/12/2021");
	
	assert(strcmp(getMaterialName(m1), "Bread") == 0);
	assert(strcmp(getMaterialSupplier(m1), "Lidl") == 0);
	assert(*(getMaterialQuantity(m1)) == 10);
	assert(equalDates(getMaterialExpirationDate(m1), d1));

	destroyMaterial(m1);
	destroyDate(d1);
}

void testMaterialToString() {
	char repr[BUFSIZE];
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");
	
	materialToString(m1, repr);
	assert(strcmp("Material: name - Bread, supplier - Lidl, quantity - 10, exp_date - 10/12/2021", repr) == 0);

	destroyMaterial(m1);
}

void testEqualMaterials() {
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");
	Material* m2 = createMaterial("Bread", "Lidl", 50, "10/12/2021");

	assert(equalMaterials(m1, m2));

	destroyMaterial(m1);
	destroyMaterial(m2);
}

void testEqualMaterialsData() {
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");
	Date* d1 = createDate("10/12/2021");

	assert(equalMaterialsData(m1, "Bread", "Lidl", d1));

	destroyMaterial(m1);
	destroyDate(d1);
}

void testCreateDate() {
	Date* d1 = createDate("10/12/2021");

	assert(getDateDay(d1) == 10);
	assert(getDateMonth(d1) == 12);
	assert(getDateYear(d1) == 2021);

	destroyDate(d1);
}

void testGetDayFromString() {
	char date[BUFSIZE] = "10/12/2021";
	Date* d1 = createDate(date);

	assert(getDayFromString(date) == getDateDay(d1));
	destroyDate(d1);
}

void testGetMonthFromString() {
	char date[BUFSIZE] = "10/12/2021";
	Date* d1 = createDate(date);

	assert(getMonthFromString(date) == getDateMonth(d1));
	destroyDate(d1);
}

void testGetYearFromString() {
	char date[BUFSIZE] = "10/12/2021";
	Date* d1 = createDate(date);

	assert(getYearFromString(date) == getDateYear(d1));
	destroyDate(d1);
}

void testLeapDateYear() {
	char date[BUFSIZE] = "10/12/2021";
	Date* d1 = createDate(date);

	assert(!leapDateYear(d1));
	setDateYear(d1, 2000);
	assert(leapDateYear(d1));
	
	destroyDate(d1);
}

void testEqualDates() {
	char date[BUFSIZE] = "10/12/2021";
	Date* d1 = createDate(date);

	strcpy(date, "11/12/2021");
	Date* d2 = createDate(date);
	Date* d3 = createDate(date);

	assert(!equalDates(d1, d2));
	assert(equalDates(d2, d3));

	destroyDate(d1);
	destroyDate(d2);
	destroyDate(d3);
}

void testCreateDynamicArray() {
	DynamicArray* da = createDynamicArray(100);
	assert(da->capacity == 100);
	destroyDynamicArray(da, NULL);
}

void testAddDA() {
	DynamicArray* da = createDynamicArray(100);
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");

	addDA(da, m1);
	assert(equalMaterials(da->data[0], m1));

	destroyDynamicArray(da, &destroyMaterial);
}

void testResizeDA() {
	DynamicArray* da = createDynamicArray(100);
	
	resizeDA(da);
	assert(da->capacity == 200);

	destroyDynamicArray(da, NULL);
}

void testGetIndexDA() {
	DynamicArray* da = createDynamicArray(100);
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");

	addDA(da, m1);
	assert(getIndexDA(da, m1, &equalMaterials) == 0);

	destroyDynamicArray(da, &destroyMaterial);
}

void testGetSizeDA() {
	DynamicArray* da = createDynamicArray(100);
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");

	addDA(da, m1);
	assert(getSizeDA(da) == 1);

	destroyDynamicArray(da, &destroyMaterial);
}

void testRemoveDA() {
	DynamicArray* da = createDynamicArray(100);
	Material* m1 = createMaterial("Bread", "Lidl", 10, "10/12/2021");

	addDA(da, m1);
	removeDA(da, m1, destroyMaterial, equalMaterials);

	assert(!getSizeDA(da));

	destroyDynamicArray(da, &destroyMaterial);
}
