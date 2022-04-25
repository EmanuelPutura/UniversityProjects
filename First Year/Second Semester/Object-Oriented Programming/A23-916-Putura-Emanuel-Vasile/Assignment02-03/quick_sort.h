/*
*  QuickSort Module. Implements the quick sort sorting method (considered to be generically - can sort any objects in any order)
*/

#pragma once

#include <stdbool.h>

int partition(void** arr, int low, int high, bool (*greaterFunc)(void*, void*), void* (*getFunc)(void*), void (*swapFunc)(void*, void*));

void quickSort(void** arr, int low, int high, bool (*greaterFunc)(void*, void*), void* (*getFunc)(void*), void (*swapFunc)(void*, void*));
