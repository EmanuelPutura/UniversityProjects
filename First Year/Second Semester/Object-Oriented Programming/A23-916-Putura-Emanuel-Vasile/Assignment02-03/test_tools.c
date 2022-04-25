#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "material.h"
#include "quick_sort.h"

bool greaterNameFunc(char* a, char* b) {
	return strcmp(a, b) > 0;
}

void testQuickSort() {
	int n = 7;
	Material** arr = (Material**)malloc(n * sizeof(Material*));
	if (arr == NULL) return;

	char* names[] = { "Bread", "Donnut", "Muffin", "Apple Pie", "Pie", "Pear Pie", "Croissant"};
	char* suppliers[] = { "Kaufland", "Lidl", "Auchan", "Auchan", "Penny", "La 2 pasi", "Lidl" };
	int quantities[] = { 10, 20, 10, 5, 9, 100, 35 };
	char* dates[] = {"10/10/2021", "12/10/2021", "09/07/2020", "10/10/2001", "11/12/2031", "15/10/2003", "25/01/2001"};

	for (int i = 0; i < n; ++i) {
		arr[i] = createMaterial(names[i], suppliers[i], quantities[i], dates[i]);
		if (arr[i] == NULL) return;
	}

	quickSort(arr, 0, n - 1, &greaterNameFunc, &getMaterialName, swapMaterials);
	assert(!strcmp(getMaterialName(arr[0]), "Apple Pie"));

	quickSort(arr, 0, n - 1, &greaterNameFunc, &getMaterialSupplier, swapMaterials);
	assert(!strcmp(getMaterialSupplier(arr[0]), "Auchan"));

	for (int i = 0; i < n; ++i)
		destroyMaterial(arr[i]);
	free(arr);
}
