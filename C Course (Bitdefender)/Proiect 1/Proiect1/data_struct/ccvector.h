#pragma once

typedef struct _CC_VECTOR {
    int *Array;
    int Size;
    int Count;
} CC_VECTOR;

int VecCreate(CC_VECTOR **Vector);
int VecDestroy(CC_VECTOR **Vector);

int VecInsertTail(CC_VECTOR *Vector, int Value);
int VecInsertHead(CC_VECTOR *Vector, int Value);
int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value);
int VecRemoveByIndex(CC_VECTOR *Vector, int Index);
int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value);

// Returns the number of element in Vector or -1 in case of error or invalid parameters
int VecGetCount(CC_VECTOR *Vector);
int VecClear(CC_VECTOR *Vector);

// Sort the vector in decreasing order
int VecSort(CC_VECTOR *Vector);

// Appends all the elements in DestVector to SrcVector
int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector);

// Resizes the vector by reallocating the memory, increasing the capacity of the vector
static int ResizeVector(CC_VECTOR *Vector);

// helper function for the QuickSort Algortihm
static int QuickSortPartition(CC_VECTOR *Vector, int begin, int end);

// QuickSort Algorithm
static int QuickSort(CC_VECTOR *Vector, int begin, int end);
