#pragma once

#include "ccvector.h"

typedef struct _CC_HEAP{
    int* Array;
    int Size;
    int Count;

    int IsMaxHeap; // 0 if min heap, otherwise max heap
} CC_HEAP;

// HpCreateMaxHeap and HpCreateMinHeap should create a max heap or a min heap,
// respectively. InitialElements is an optional parameter and, if it is not null, the constructed
// heap should initially contain all the elements in the provided vector.
int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements);
int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements);
int HpDestroy(CC_HEAP **Heap);

int HpInsert(CC_HEAP *Heap, int Value);

// HpRemove should remove all elements with the value Value in the heap
int HpRemove(CC_HEAP *Heap, int Value);

// HpGetExtreme should return the maximum/minimum value in the heap, depending on the
// type of heap constructed
int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue);

// HpPopExtreme should return the maximum/minimum value in the heap, and remove all
// instances of said value from the heap
int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue);

// Returns the number of elements in Heap or -1 in case of error or invalid parameter
int HpGetElementCount(CC_HEAP *Heap);

// HpSortToVector should construct and return (in the SortedVector parameter) a vector
// sorted in increasing order containing all the elements present in the heap
int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector);

static int GetLeavesNumber(CC_HEAP* Heap);

static int MinHeapify(CC_HEAP* MinHeap, int index);

static int MaxHeapify(CC_HEAP* MaxHeap, int index);

static int MaxHeapifyVector(CC_VECTOR* Vector, int index);

static int MinHeapBubbleUp(CC_HEAP* MinHeap, int index);

static int MaxHeapBubbleUp(CC_HEAP* MaxHeap, int index);

static int BuildMaxHeap(CC_HEAP* MaxHeap);

static int BuildMinHeap(CC_HEAP* MinHeap);

static int ResizeHeap(CC_HEAP* Heap);
