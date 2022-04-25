#include "dynamic_array.h"

#include <stdlib.h>

DynamicArray* createDynamicArray(int capacity) {
	if (capacity < 0) return NULL;
	DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (array == NULL) return NULL;

	array->length = 0;
	array->capacity = capacity;
	array->data = (void**)malloc(capacity * sizeof(void*));

	return array;
}

DynamicArray* copyDynamicArray(DynamicArray* array, void* (*copyFunc)(void*)) {
	DynamicArray* new_array = createDynamicArray(array->capacity);
	new_array->length = array->length;

	for (int i = 0; i < array->length; ++i)
		new_array->data[i] = copyFunc(array->data[i]);
	return new_array;
}

void addDA(DynamicArray* array, void* element) {
	if (array->length == array->capacity) resizeDA(array);
	array->data[array->length++] = element;
}

void addToIndexDA(DynamicArray* array, void* element, int index) {
	if (array->length == array->capacity) resizeDA(array);
	array->length++;

	for (int i = array->length; i > index; i--)
		array->data[i] = array->data[i - 1];

	array->data[index] = element;
}

void resizeDA(DynamicArray* array) {
	array->capacity *= 2;
	void** new_data = realloc(array->data, array->capacity * sizeof(void*));
	if (new_data != NULL) array->data = new_data;
}

int getIndexDA(DynamicArray* array, void* element, bool (*equalFunc)(void*, void*)) {
	for (int i = 0; i < array->length; ++i)
		if (equalFunc(array->data[i], element)) return i;
	return -1;
}

int getSizeDA(DynamicArray* array) {
	return array->length;
}

void setSizeDA(DynamicArray* array, int length) {
	array->length = length;
}

int getCapacityDA(DynamicArray* array) {
	return array->capacity;
}

void* getElementDA(DynamicArray* array, int index) {
	if (index < 0 || index >= array->length) return NULL;
	return array->data[index];
}

void** getDataDA(DynamicArray* array) {
	return array->data;
}

void updateDA(DynamicArray* array, int index, void (*setFunc)(void*, const void*), const void* new_value) {
	setFunc(array->data[index], new_value);
}

int removeDA(DynamicArray* array, void* element, void (*destroyFunc)(void*), bool (*equalFunc)(void*, void*)) {
	int index = getIndexDA(array, element, equalFunc);
	if (index == -1) return -1;

	if (destroyFunc != NULL) destroyFunc(array->data[index]);
	for (int i = index + 1; i < array->length; ++i) {
		array->data[i - 1] = array->data[i];
	}

	array->length--;
	return 0;
}

void destroyDynamicArray(DynamicArray* array, void (*destroyFunc)(void*)) {
	for (int i = 0; i < array->length; ++i)
		destroyFunc(array->data[i]);
	free(array->data);
	free(array);
}
