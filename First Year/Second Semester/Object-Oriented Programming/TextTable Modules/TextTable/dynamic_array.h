#pragma once
#include <stdbool.h>

typedef struct {
	void** data;
	int length, capacity;
} DynamicArray;

DynamicArray* createDynamicArray(int capacity);

void addDA(DynamicArray* array, void* element);

void addToIndexDA(DynamicArray* array, void* element, int index);

void resizeDA(DynamicArray* array);

int getIndexDA(DynamicArray* array, void* element, bool (*equalFunc)(void*, void*));

int getSizeDA(DynamicArray* array);

int getCapacityDA(DynamicArray* array);

void* getElementDA(DynamicArray* array, int index);

void** getDataDA(DynamicArray* array);

void updateDA(DynamicArray* array, int index, void (*setFunc)(void*, const void*), const void* new_value);

int removeDA(DynamicArray* array, void* element, void (*destroyFunc)(void*), bool (*equalFunc)(void*, void*));

void destroyDynamicArray(DynamicArray* array, void (*destroyFunc)(void*));
