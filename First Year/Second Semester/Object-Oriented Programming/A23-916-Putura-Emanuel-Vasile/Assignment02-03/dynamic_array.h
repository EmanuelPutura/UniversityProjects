/*
*  DynamicArray module
*/

#pragma once
#include <stdbool.h>

/*
*  DynamicArray structure
*/
typedef struct {
	void** data;
	int length, capacity;
} DynamicArray;

/*
*  Creates a DynamicArray object
*/
DynamicArray* createDynamicArray(int capacity);

/*
*  Copies the attributes of a DynamicArray to another one
*/
DynamicArray* copyDynamicArray(DynamicArray* array, void* (*copyFunc)(void*));

/*
*  Adds an element to a DynamicArray object
*/
void addDA(DynamicArray* array, void* element);

/*
*  Adds an element at a specified index in a DynamicArray object
*/
void addToIndexDA(DynamicArray* array, void* element, int index);

/*
*  Resizes a DynamicArray object
*/
void resizeDA(DynamicArray* array);

/*
*  Gets the index of an element from a DynamicArray object
*/
int getIndexDA(DynamicArray* array, void* element, bool (*equalFunc)(void*, void*));

/*
*  Gets the size of a DynamicArray object (the number of elements)
*/
int getSizeDA(DynamicArray* array);

/*
*  Sets the size of DynamicArray object
*/
void setSizeDA(DynamicArray* array, int length);

/*
*  Gets the capacity of a DynamicArray object
*/
int getCapacityDA(DynamicArray* array);

/*
*  Gets the element from a specified index in a DynamicArray object
*/
void* getElementDA(DynamicArray* array, int index);

/*
*  Gets all the data in a DynamicArray object
*/
void** getDataDA(DynamicArray* array);

/*
*  Generic update function for an element of a DynamicArray object
*/
void updateDA(DynamicArray* array, int index, void (*setFunc)(void*, const void*), const void* new_value);

/*
*  Removes an element from a DynamicArray object
*/
int removeDA(DynamicArray* array, void* element, void (*destroyFunc)(void*), bool (*equalFunc)(void*, void*));

/*
*  Destroys a DynamicArray object
*/
void destroyDynamicArray(DynamicArray* array, void (*destroyFunc)(void*));
